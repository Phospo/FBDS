#include "canvaspanel.h"

#include "ui_canvaspanel.h"

CanvasPanel::CanvasPanel(QWidget* _parent)
    : QWidget(_parent), FUi(std::make_unique<Ui::CanvasPanel>()) {
    FUi->setupUi(this);
}

CanvasPanel::~CanvasPanel() = default;

void CanvasPanel::clearScene() {
    FUi->canvasView->clearScene();
}