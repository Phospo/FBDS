#include "dashboardview.h"

#include "ui_dashboardview.h"

#include <QPushButton>

DashboardView::DashboardView(QWidget* _parent)
    : QWidget(_parent), FUi(std::make_unique<Ui::DashboardView>()) {
    FUi->setupUi(this);

    connect(FUi->runStepButton, &QPushButton::clicked, this, [this]() {
        emit runStepRequested();
    });
}

void DashboardView::appendLog(const QString& _text) {
    FUi->logView->appendPlainText(_text);
}

void DashboardView::appendSimulationOutput(const QString& _text) {
    FUi->simulationOutputView->appendPlainText(_text);
}
