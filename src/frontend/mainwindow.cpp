#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>

#include "simulatorbridge.h"
#include "views/dashboardview.h"

CMainWindow::CMainWindow(QWidget* _parent)
    : QMainWindow(_parent), FUi(std::make_unique<Ui::MainWindow>()), FSimulatorBridge(new CSimulatorBridge(this)) {
    FUi->setupUi(this);

    FUi->mainSplitter->setStretchFactor(0, 5);
    FUi->mainSplitter->setStretchFactor(1, 2);
    FUi->mainSplitter->setStretchFactor(2, 3);

    connect(FUi->actionNewScheme, &QAction::triggered, this, &CMainWindow::onNewScheme);
    connect(FUi->actionOpenScheme, &QAction::triggered, this, &CMainWindow::onOpenScheme);
    connect(FUi->actionSaveScheme, &QAction::triggered, this, &CMainWindow::onSaveScheme);
    connect(FUi->actionRunSimulation, &QAction::triggered, this, &CMainWindow::onRunSimulation);
    connect(FUi->dashboardView, &DashboardView::runStepRequested, this, &CMainWindow::onRunSimulation);

    statusBar()->showMessage("Gotowy");
}

CMainWindow::~CMainWindow() = default;

void CMainWindow::onNewScheme() {
    FUi->canvasPanel->clearScene();
    FUi->propertyPanel->resetState();
    FUi->dashboardView->appendLog("Utworzono nowy schemat.");
    statusBar()->showMessage("Nowy schemat");
}

void CMainWindow::onOpenScheme() {
    const QString path = QFileDialog::getOpenFileName(
        this,
        "Wybierz plik schematu",
        QString(),
        "JSON (*.json)"
    );

    if (path.isEmpty()) {
        return;
    }

    FUi->dashboardView->appendLog("Wybrano plik: " + path);
    statusBar()->showMessage("Wczytywanie: " + path);

    const bool loadOk = FSimulatorBridge->loadConfigurationFromJSON(path);
    if (loadOk) {
        FUi->dashboardView->appendLog("Konfiguracja JSON zostala wczytana.");
        statusBar()->showMessage("Wczytano konfiguracje JSON");
        QMessageBox::information(this, "Wczytywanie", "Konfiguracja zostala poprawnie wczytana.");
        return;
    }

    FUi->dashboardView->appendLog("Blad wczytywania konfiguracji JSON.");
    statusBar()->showMessage("Blad wczytywania JSON");
    QMessageBox::warning(this, "Wczytywanie", "Nie udalo sie wczytac konfiguracji JSON.");
}

void CMainWindow::onSaveScheme() {
    const QString path = QFileDialog::getSaveFileName(
        this,
        "Zapisz schemat",
        QString(),
        "JSON (*.json)"
    );

    if (path.isEmpty()) {
        return;
    }

    FUi->dashboardView->appendLog("Docelowy plik zapisu: " + path);
    statusBar()->showMessage("Zapisywanie: " + path);

    const bool saveOk = FSimulatorBridge->saveConfigurationToJSON(path);
    if (saveOk) {
        FUi->dashboardView->appendLog("Konfiguracja JSON zostala zapisana.");
        statusBar()->showMessage("Zapisano konfiguracje JSON");
        QMessageBox::information(this, "Zapisywanie", "Konfiguracja zostala poprawnie zapisana.");
        return;
    }

    FUi->dashboardView->appendLog("Blad zapisu konfiguracji JSON.");
    statusBar()->showMessage("Blad zapisu JSON");
    QMessageBox::warning(this, "Zapisywanie", "Nie udalo sie zapisac konfiguracji JSON.");
}

void CMainWindow::onRunSimulation() {
    FUi->dashboardView->appendLog("Uruchamianie domyslnej symulacji backendu...");
    const bool runOk = FSimulatorBridge->runDefaultSimulation();

    if (runOk) {
        FUi->dashboardView->appendLog("Symulacja zakonczona.");
        statusBar()->showMessage("Symulacja zakonczona");
        return;
    }

    FUi->dashboardView->appendLog("Nieudane uruchomienie symulacji.");
    statusBar()->showMessage("Blad uruchomienia");
}
