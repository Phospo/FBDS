#pragma once

#include <QGraphicsView>
#include <QList>
#include <QPointF>
#include <QString>

class QGraphicsScene;

/** FBDCanvasView

    Widok sceny schematu FBD oparty o QGraphicsView.
*/
class FBDCanvasView : public QGraphicsView {
    Q_OBJECT

public:
    /**
        Dane bloku FBD używane do edycji i serializacji.
    */
    struct FBDBlockData {
        QString Name;
        QString Type;
        unsigned InputCount{1};
        double ConstValue{0.0};
        double InitialOutput{0.0};
        double Frequency{1.0};
        double Amplitude{1.0};
        double Phase{0.0};
        double Offset{0.0};
        int RoundingPrecision{-1};
        QPointF Position{0.0, 0.0};
    };

    /**
        Dane połączenia FBD używane do edycji i serializacji.
    */
    struct FBDConnectionData {
        QString FromBlock;
        unsigned FromOutput{1};
        QString ToBlock;
        unsigned ToInput{1};
    };

    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit FBDCanvasView(QWidget* _parent = nullptr);

    /**
        Czyszczenie bieżącej sceny.
    */
    void clearScene();

    /**
        Dodanie nowego bloku do sceny.
    */
    void addBlock(const FBDBlockData& _data);

    /**
        Wczytanie schematu z pliku JSON.

        @param path Ścieżka do pliku JSON
        @return true, jeśli schemat został poprawnie wczytany
    */
    bool loadFromJson(const QString& path);

    /**
        Zapisanie bieżącego schematu do pliku JSON.

        @param path Ścieżka do pliku JSON
        @return true, jeśli zapis się powiódł
    */
    bool saveToJson(const QString& path) const;

    /**
        Eksport bieżącego schematu do tekstu JSON.

        @return Tekst JSON schematu
    */
    QString exportToJson() const;

    /**
        Usunięcie zaznaczonego bloku wraz z powiązanymi połączeniami.
    */
    void deleteSelected();

    /**
        Zastosowanie zmiany właściwości do zaznaczonego bloku.

        @param propertyName Nazwa właściwości
        @param propertyValue Wartość właściwości
    */
    void setSelectedBlockProperty(const QString& propertyName, const QString& propertyValue);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

signals:
    /**
        Zgłoszenie zmiany zaznaczonego bloku.
    */
    void blockSelected(const FBDBlockData& blockData);

    /**
        Żądanie dodania bloku z menu kontekstowego.
    */
    void addBlockRequested();

    /**
        Żądanie usunięcia zaznaczonego elementu.
    */
    void deleteSelectedRequested();

private:
    class FBDBlockItem;
    class FBDConnectionItem;

    QGraphicsScene* FScene{nullptr};
    QList<FBDConnectionItem*> FConnections;
    QList<FBDBlockItem*> FBlocks;

    struct SPendingPort {
        FBDBlockItem* Block{nullptr};
        bool IsOutput{false};
        unsigned Index{0};
    };

    SPendingPort FPendingPort;

    void clearPendingPort();
    void createConnection(FBDBlockItem* source, unsigned sourceOutput, FBDBlockItem* target, unsigned targetInput);
    void removeConnectionsForBlock(FBDBlockItem* block);
    bool connectionExists(FBDBlockItem* source, unsigned sourcePort, FBDBlockItem* dest, unsigned destPort) const;
    FBDBlockItem* selectedBlockItem() const;
    void handlePortClick(FBDBlockItem* block, bool isOutput, unsigned index);
    void emitCurrentSelection();
    QString uniqueBlockName(const QString& prefix) const;
    void onSceneSelectionChanged();
};
