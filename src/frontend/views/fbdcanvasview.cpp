#include "fbdcanvasview.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>

FBDCanvasView::FBDCanvasView(QWidget* _parent)
    : QGraphicsView(_parent),
      FScene(new QGraphicsScene(this)) {
    setScene(FScene);
    setRenderHint(QPainter::Antialiasing, true);

    FScene->setSceneRect(0.0, 0.0, 1200.0, 700.0);

    // Tymczasowy blok referencyjny, aby potwierdzić dzialanie widoku.
    QGraphicsRectItem* demoBlock = FScene->addRect(40.0, 40.0, 180.0, 80.0, QPen(Qt::black));
    demoBlock->setToolTip("Blok demonstracyjny");
}

void FBDCanvasView::clearScene() {
    FScene->clear();
}
