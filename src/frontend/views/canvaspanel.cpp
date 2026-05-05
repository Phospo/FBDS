#include "canvaspanel.h"

#include "ui_canvaspanel.h"

CanvasPanel::CanvasPanel(QWidget* _parent)
    : QWidget(_parent), FUi(std::make_unique<Ui::CanvasPanel>()) {
    FUi->setupUi(this);
    connect(FUi->canvasView, &FBDCanvasView::blockSelected, this, &CanvasPanel::blockSelected);
    connect(FUi->canvasView, &FBDCanvasView::addBlockRequested, this, &CanvasPanel::addBlockRequested);
    connect(FUi->canvasView, &FBDCanvasView::deleteSelectedRequested, this, &CanvasPanel::deleteSelectedRequested);
}

CanvasPanel::~CanvasPanel() = default;

void CanvasPanel::clearScene() {
    FUi->canvasView->clearScene();
}

void CanvasPanel::addBlock(const FBDCanvasView::FBDBlockData& _data) {
    FUi->canvasView->addBlock(_data);
}

bool CanvasPanel::loadFromJson(const QString& _path) {
    return FUi->canvasView->loadFromJson(_path);
}

bool CanvasPanel::saveToJson(const QString& _path) const {
    return FUi->canvasView->saveToJson(_path);
}

QString CanvasPanel::exportToJson() const {
    return FUi->canvasView->exportToJson();
}

void CanvasPanel::deleteSelectedBlock() {
    FUi->canvasView->deleteSelected();
}

void CanvasPanel::setSelectedBlockProperty(const QString& _propertyName, const QString& _propertyValue) {
    FUi->canvasView->setSelectedBlockProperty(_propertyName, _propertyValue);
}
