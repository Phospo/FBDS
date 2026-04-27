#pragma once

#include <QGraphicsView>

class QGraphicsScene;

/** FBDCanvasView

    Widok sceny schematu FBD oparty o QGraphicsView.
*/
class FBDCanvasView : public QGraphicsView {
    Q_OBJECT

private:
    /** Scena przechowująca elementy schematu. */
    QGraphicsScene* FScene{nullptr};

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit FBDCanvasView(QWidget* _parent = nullptr);

    /**
        Czyszczenie bieżącej sceny.
    */
    void clearScene();
};
