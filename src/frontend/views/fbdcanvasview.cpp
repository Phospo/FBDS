#include "fbdcanvasview.h"

#include <QContextMenuEvent>
#include <QFile>
#include <QGraphicsObject>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

namespace {
static constexpr qreal kBlockWidth = 180.0;
static constexpr qreal kBaseBlockHeight = 60.0;
static constexpr qreal kPortSpacing = 20.0;
static constexpr qreal kPortRadius = 6.0;
static constexpr qreal kBlockMarginX = 220.0;

QString toString(const QVariant& value) {
    return value.toString();
}
}

class FBDCanvasView::FBDBlockItem : public QGraphicsObject {
public:
    FBDBlockItem(const FBDCanvasView::FBDBlockData& data, FBDCanvasView* canvas)
        : FCanvas(canvas), FBlockData(data) {
        setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
        setAcceptHoverEvents(true);
    }

    QRectF boundingRect() const override {
        return QRectF(0.0, 0.0, kBlockWidth, blockHeight());
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        Q_UNUSED(widget)

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(QPen(isSelected() ? Qt::blue : Qt::black, 1.5));
        painter->setBrush(isSelected() ? QColor(220, 235, 255) : Qt::white);
        painter->drawRoundedRect(boundingRect(), 6.0, 6.0);

        painter->setPen(Qt::black);
        painter->drawText(boundingRect().adjusted(8, 8, -8, -8), Qt::AlignLeft | Qt::AlignTop, FBlockData.Name);
        painter->drawText(boundingRect().adjusted(8, 24, -8, -8), Qt::AlignLeft | Qt::AlignTop, FBlockData.Type);

        for (unsigned index = 1; index <= FBlockData.InputCount; ++index) {
            const QPointF port = inputPortLocalPosition(index);
            painter->setBrush(Qt::gray);
            painter->drawEllipse(port, kPortRadius, kPortRadius);
        }

        const QPointF outPort = outputPortLocalPosition();
        painter->setBrush(Qt::green);
        painter->drawEllipse(outPort, kPortRadius, kPortRadius);
    }

    bool hitInputPort(const QPointF& position, unsigned& index) const {
        for (unsigned i = 1; i <= FBlockData.InputCount; ++i) {
            const QPointF port = inputPortLocalPosition(i);
            if (QLineF(position, port).length() <= kPortRadius * 1.5) {
                index = i;
                return true;
            }
        }
        return false;
    }

    bool hitOutputPort(const QPointF& position, unsigned& index) const {
        const QPointF port = outputPortLocalPosition();
        if (QLineF(position, port).length() <= kPortRadius * 1.5) {
            index = 1;
            return true;
        }
        return false;
    }

    QPointF inputPortScenePosition(unsigned inputIndex) const {
return mapToScene(inputPortLocalPosition(inputIndex).toPoint());
}

    QPointF outputPortScenePosition(unsigned outputIndex = 1) const {
        Q_UNUSED(outputIndex)
        return mapToScene(outputPortLocalPosition().toPoint());
    }

    const FBDCanvasView::FBDBlockData& blockData() const {
        return FBlockData;
    }

    void setBlockData(const FBDCanvasView::FBDBlockData& data) {
        prepareGeometryChange();
        FBlockData = data;
        update();
    }

    void applyProperty(const QString& property, const QString& value) {
        if (property == "Name") {
            FBlockData.Name = value;
        } else if (property == "InputCount") {
            const int newCount = qMax(1, value.toInt());
            if (newCount != static_cast<int>(FBlockData.InputCount)) {
                FBlockData.InputCount = static_cast<unsigned>(newCount);
                prepareGeometryChange();
                if (FCanvas) {
                    FCanvas->removeConnectionsForBlock(this);
                }
            }
        } else if (property == "ConstValue") {
            FBlockData.ConstValue = value.toDouble();
        } else if (property == "InitialOutput") {
            FBlockData.InitialOutput = value.toDouble();
        } else if (property == "Frequency") {
            FBlockData.Frequency = value.toDouble();
        } else if (property == "Amplitude") {
            FBlockData.Amplitude = value.toDouble();
        } else if (property == "Phase") {
            FBlockData.Phase = value.toDouble();
        } else if (property == "Offset") {
            FBlockData.Offset = value.toDouble();
        } else if (property == "RoundingPrecision") {
            FBlockData.RoundingPrecision = value.toInt();
        }
        update();
    }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override {
        if (change == ItemPositionHasChanged && scene()) {
            scene()->update();
        }
        return QGraphicsObject::itemChange(change, value);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsObject::mousePressEvent(event);
    }

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() != Qt::LeftButton) {
            QGraphicsObject::mouseDoubleClickEvent(event);
            return;
        }

        unsigned index = 0;
        if (FCanvas && FCanvas->isVisible()) {
            if (hitOutputPort(event->pos(), index)) {
                if (FCanvas->scene()) {
                    FCanvas->handlePortClick(this, true, index);
                    event->accept();
                    return;
                }
            }
            if (hitInputPort(event->pos(), index)) {
                if (FCanvas->scene()) {
                    FCanvas->handlePortClick(this, false, index);
                    event->accept();
                    return;
                }
            }
        }

        QGraphicsObject::mouseDoubleClickEvent(event);
    }

    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override {
        unsigned unused = 0;
        if (hitInputPort(event->pos(), unused) || hitOutputPort(event->pos(), unused)) {
            setCursor(Qt::PointingHandCursor);
        } else {
            setCursor(Qt::OpenHandCursor);
        }
        QGraphicsObject::hoverMoveEvent(event);
    }

private:
    QPointF inputPortLocalPosition(unsigned index) const {
        const qreal top = 20.0 + (index - 1) * kPortSpacing;
        return QPointF(8.0, top);
    }

    QPointF outputPortLocalPosition() const {
        return QPointF(kBlockWidth - 8.0, boundingRect().center().y());
    }

    qreal blockHeight() const {
        return kBaseBlockHeight + kPortSpacing * qMax(0, static_cast<int>(FBlockData.InputCount) - 1);
    }

    FBDCanvasView* FCanvas{nullptr};
    FBDCanvasView::FBDBlockData FBlockData;
};

class FBDCanvasView::FBDConnectionItem : public QGraphicsPathItem {
public:
    FBDConnectionItem(FBDBlockItem* from,
                      unsigned fromOutput,
                      FBDBlockItem* to,
                      unsigned toInput)
        : FFrom(from), FFromOutput(fromOutput), FTo(to), FToInput(toInput) {
        setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        setZValue(-1);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        setPath(currentPath());
        QGraphicsPathItem::paint(painter, option, widget);
    }

    FBDBlockItem* fromBlock() const {
        return FFrom;
    }

    unsigned fromOutput() const {
        return FFromOutput;
    }

    FBDBlockItem* toBlock() const {
        return FTo;
    }

    unsigned toInput() const {
        return FToInput;
    }

    QString fromBlockName() const {
        return FFrom != nullptr ? FFrom->blockData().Name : QString();
    }

    QString toBlockName() const {
        return FTo != nullptr ? FTo->blockData().Name : QString();
    }

private:
    QPainterPath currentPath() const {
        QPainterPath path;
        if (FFrom == nullptr || FTo == nullptr) {
            return path;
        }

        const QPointF source = FFrom->outputPortScenePosition(FFromOutput);
        const QPointF target = FTo->inputPortScenePosition(FToInput);
        path.moveTo(source);

        const qreal dx = qMax(40.0, qAbs(target.x() - source.x()) / 2.0);
        const QPointF control1(source.x() + dx, source.y());
        const QPointF control2(target.x() - dx, target.y());
        path.cubicTo(control1, control2, target);
        return path;
    }

    FBDBlockItem* FFrom{nullptr};
    unsigned FFromOutput{1};
    FBDBlockItem* FTo{nullptr};
    unsigned FToInput{1};
};

FBDCanvasView::FBDCanvasView(QWidget* _parent)
    : QGraphicsView(_parent),
      FScene(new QGraphicsScene(this)) {
    setScene(FScene);
    setRenderHint(QPainter::Antialiasing, true);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    FScene->setSceneRect(0.0, 0.0, 1600.0, 900.0);
    connect(FScene, &QGraphicsScene::selectionChanged, this, &FBDCanvasView::onSceneSelectionChanged);
}

void FBDCanvasView::clearScene() {
    for (FBDConnectionItem* connection : qAsConst(FConnections)) {
        FScene->removeItem(connection);
        delete connection;
    }
    FConnections.clear();

    for (FBDBlockItem* block : qAsConst(FBlocks)) {
        FScene->removeItem(block);
        delete block;
    }
    FBlocks.clear();

    FScene->clear();
    clearPendingPort();
    emitCurrentSelection();
}

void FBDCanvasView::addBlock(const FBDBlockData& _data) {
    FBDBlockData blockData = _data;
    if (blockData.Name.isEmpty()) {
        blockData.Name = uniqueBlockName(blockData.Type.isEmpty() ? "Block" : blockData.Type);
    } else if (!uniqueBlockName(blockData.Name).isEmpty()) {
        // Ensure the name is unique by renaming if necessary.
        blockData.Name = uniqueBlockName(blockData.Name);
    }

    FBDBlockItem* block = new FBDBlockItem(blockData, this);
    FBlocks.append(block);
    FScene->addItem(block);

    if (blockData.Position == QPointF(0.0, 0.0)) {
        block->setPos(40.0 + FBlocks.size() * kBlockMarginX, 40.0);
    } else {
        block->setPos(blockData.Position);
    }
    block->setSelected(true);
    emitCurrentSelection();
}

bool FBDCanvasView::loadFromJson(const QString& path) {
    QFile inputFile(path);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    const QByteArray jsonBytes = inputFile.readAll();
    inputFile.close();

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(jsonBytes, &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        return false;
    }

    const QJsonObject root = document.object();
    if (!root.value("blocks").isArray()) {
        return false;
    }

    clearScene();

    const QJsonArray blocks = root.value("blocks").toArray();
    for (const QJsonValue& blockValue : blocks) {
        if (!blockValue.isObject()) {
            clearScene();
            return false;
        }

        const QJsonObject blockObject = blockValue.toObject();
        FBDBlockData data;
        data.Name = blockObject.value("name").toString();
        data.Type = blockObject.value("type").toString();
        const QJsonObject params = blockObject.value("params").toObject();
        data.Position = QPointF(blockObject.value("x").toDouble(0.0), blockObject.value("y").toDouble(0.0));

        if (data.Type == "SinGen") {
            data.Frequency = params.value("frequency").toDouble(1.0);
            data.Amplitude = params.value("amplitude").toDouble(1.0);
            data.Phase = params.value("phase").toDouble(0.0);
            data.Offset = params.value("offset").toDouble(0.0);
            data.RoundingPrecision = params.value("roundingPrecision").toInt(-1);
        } else if (data.Type == "ConstVal") {
            data.ConstValue = params.value("value").toDouble(0.0);
        } else {
            data.InputCount = static_cast<unsigned>(params.value("inputCount").toInt(1));
            data.ConstValue = params.value("constValue").toDouble(0.0);
            data.InitialOutput = params.value("initialOutput").toDouble(0.0);
        }

        addBlock(data);
    }

    if (root.value("connections").isArray()) {
        const QJsonArray connections = root.value("connections").toArray();
        for (const QJsonValue& connectionValue : connections) {
            if (!connectionValue.isObject()) {
                clearScene();
                return false;
            }

            const QJsonObject connectionObject = connectionValue.toObject();
            QString fromBlockName;
            unsigned fromOutput = 1;
            QString toBlockName;
            unsigned toInput = 1;

            if (connectionObject.value("from").isObject()) {
                const QJsonObject fromObject = connectionObject.value("from").toObject();
                fromBlockName = fromObject.value("block").toString();
                fromOutput = static_cast<unsigned>(fromObject.value("output").toInt(1));
            } else {
                fromBlockName = connectionObject.value("fromBlock").toString();
                fromOutput = static_cast<unsigned>(connectionObject.value("fromOutput").toInt(1));
            }

            if (connectionObject.value("to").isObject()) {
                const QJsonObject toObject = connectionObject.value("to").toObject();
                toBlockName = toObject.value("block").toString();
                toInput = static_cast<unsigned>(toObject.value("input").toInt(1));
            } else {
                toBlockName = connectionObject.value("toBlock").toString();
                toInput = static_cast<unsigned>(connectionObject.value("toInput").toInt(1));
            }

            FBDBlockItem* fromBlock = nullptr;
            FBDBlockItem* toBlock = nullptr;
            for (FBDBlockItem* block : qAsConst(FBlocks)) {
                if (block->blockData().Name == fromBlockName) {
                    fromBlock = block;
                }
                if (block->blockData().Name == toBlockName) {
                    toBlock = block;
                }
            }

            if (fromBlock == nullptr || toBlock == nullptr) {
                continue;
            }

            createConnection(fromBlock, fromOutput, toBlock, toInput);
        }
    }

    return true;
}

bool FBDCanvasView::saveToJson(const QString& path) const {
    const QString json = exportToJson();
    QFile outputFile(path);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    const QByteArray bytes = json.toUtf8();
    const qint64 written = outputFile.write(bytes);
    outputFile.close();
    return written == bytes.size();
}

QString FBDCanvasView::exportToJson() const {
    QJsonObject root;
    root.insert("samplingTime", 10);
    root.insert("simulationSteps", 100);

    QJsonArray blocks;
    for (const FBDBlockItem* block : qAsConst(FBlocks)) {
        const auto& data = block->blockData();
        QJsonObject blockObject;
        blockObject.insert("name", data.Name);
        blockObject.insert("type", data.Type);

        QJsonObject params;
        if (data.Type == "SinGen") {
            params.insert("frequency", data.Frequency);
            params.insert("amplitude", data.Amplitude);
            params.insert("phase", data.Phase);
            params.insert("offset", data.Offset);
            params.insert("roundingPrecision", data.RoundingPrecision);
        } else if (data.Type == "ConstVal") {
            params.insert("value", data.ConstValue);
        } else {
            params.insert("inputCount", static_cast<int>(data.InputCount));
            params.insert("constValue", data.ConstValue);
            params.insert("initialOutput", data.InitialOutput);
        }

        blockObject.insert("params", params);
        blockObject.insert("x", block->pos().x());
        blockObject.insert("y", block->pos().y());
        blocks.push_back(blockObject);
    }
    root.insert("blocks", blocks);

    QJsonArray connections;
    for (const FBDConnectionItem* connection : qAsConst(FConnections)) {
        QJsonObject connectionObject;
        QJsonObject fromObject;
        fromObject.insert("block", connection->fromBlockName());
        fromObject.insert("output", static_cast<int>(connection->fromOutput()));
        connectionObject.insert("from", fromObject);

        QJsonObject toObject;
        toObject.insert("block", connection->toBlockName());
        toObject.insert("input", static_cast<int>(connection->toInput()));
        connectionObject.insert("to", toObject);
        connections.push_back(connectionObject);
    }
    root.insert("connections", connections);

    return QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Indented));
}

void FBDCanvasView::deleteSelected() {
    const QList<QGraphicsItem*> selectedItems = FScene->selectedItems();
    for (QGraphicsItem* item : selectedItems) {
        FBDBlockItem* block = dynamic_cast<FBDBlockItem*>(item);
        if (block != nullptr) {
            removeConnectionsForBlock(block);
            FBlocks.removeOne(block);
            FScene->removeItem(block);
            delete block;
        }
    }
    emitCurrentSelection();
}

void FBDCanvasView::setSelectedBlockProperty(const QString& propertyName, const QString& propertyValue) {
    FBDBlockItem* selected = selectedBlockItem();
    if (selected != nullptr) {
        selected->applyProperty(propertyName, propertyValue);
    }
}

void FBDCanvasView::clearPendingPort() {
    FPendingPort = SPendingPort();
}

void FBDCanvasView::createConnection(FBDBlockItem* source,
                                    unsigned sourceOutput,
                                    FBDBlockItem* target,
                                    unsigned targetInput) {
    if (source == nullptr || target == nullptr) {
        return;
    }
    if (connectionExists(source, sourceOutput, target, targetInput)) {
        return;
    }
    auto* connection = new FBDConnectionItem(source, sourceOutput, target, targetInput);
    FConnections.append(connection);
    FScene->addItem(connection);
}

void FBDCanvasView::removeConnectionsForBlock(FBDBlockItem* block) {
    QList<FBDConnectionItem*> removed;
    for (FBDConnectionItem* connection : qAsConst(FConnections)) {
        if (connection->fromBlock() == block || connection->toBlock() == block) {
            removed.append(connection);
        }
    }
    for (FBDConnectionItem* connection : qAsConst(removed)) {
        FConnections.removeOne(connection);
        FScene->removeItem(connection);
        delete connection;
    }
}

bool FBDCanvasView::connectionExists(FBDBlockItem* source,
                                     unsigned sourcePort,
                                     FBDBlockItem* dest,
                                     unsigned destPort) const {
    for (const FBDConnectionItem* connection : qAsConst(FConnections)) {
        if (connection->fromBlock() == source && connection->fromOutput() == sourcePort &&
            connection->toBlock() == dest && connection->toInput() == destPort) {
            return true;
        }
    }
    return false;
}

FBDCanvasView::FBDBlockItem* FBDCanvasView::selectedBlockItem() const {
    const QList<QGraphicsItem*> selectedItems = FScene->selectedItems();
    for (QGraphicsItem* item : selectedItems) {
        FBDBlockItem* block = dynamic_cast<FBDBlockItem*>(item);
        if (block != nullptr) {
            return block;
        }
    }
    return nullptr;
}

void FBDCanvasView::handlePortClick(FBDBlockItem* block, bool isOutput, unsigned index) {
    if (FPendingPort.Block == nullptr) {
        FPendingPort.Block = block;
        FPendingPort.IsOutput = isOutput;
        FPendingPort.Index = index;
        return;
    }

    // Only create a connection between different port directions.
    if (FPendingPort.IsOutput == isOutput) {
        clearPendingPort();
        return;
    }

    FBDBlockItem* source = nullptr;
    unsigned sourcePort = 1;
    FBDBlockItem* target = nullptr;
    unsigned targetPort = 1;

    if (FPendingPort.IsOutput) {
        source = FPendingPort.Block;
        sourcePort = FPendingPort.Index;
        target = block;
        targetPort = index;
    } else {
        source = block;
        sourcePort = index;
        target = FPendingPort.Block;
        targetPort = FPendingPort.Index;
    }

    createConnection(source, sourcePort, target, targetPort);
    clearPendingPort();
}

void FBDCanvasView::contextMenuEvent(QContextMenuEvent* event) {
    QMenu menu;
    QAction* addBlock = menu.addAction("Dodaj blok");
    QAction* deleteSelected = menu.addAction("Usun zaznaczony");

    const QAction* chosen = menu.exec(event->globalPos());
    if (chosen == addBlock) {
        emit addBlockRequested();
    } else if (chosen == deleteSelected) {
        emit deleteSelectedRequested();
    }
}

void FBDCanvasView::emitCurrentSelection() {
    FBDBlockItem* selected = selectedBlockItem();
    if (selected != nullptr) {
        emit blockSelected(selected->blockData());
    } else {
        emit blockSelected(FBDBlockData());
    }
}

QString FBDCanvasView::uniqueBlockName(const QString& prefix) const {
    QString base = prefix;
    if (base.isEmpty()) {
        base = "Block";
    }

    QString candidate = base;
    int suffix = 1;
    while (true) {
        bool used = false;
        for (const FBDBlockItem* block : qAsConst(FBlocks)) {
            if (block->blockData().Name == candidate) {
                used = true;
                break;
            }
        }
        if (!used) {
            return candidate;
        }
        candidate = base + QString::number(suffix++);
    }
}

void FBDCanvasView::onSceneSelectionChanged() {
    emitCurrentSelection();
}
