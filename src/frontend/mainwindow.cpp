#include "mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplitter>
#include <QStatusBar>

#include "simulatorbridge.h"
#include "views/dashboardview.h"
#include "views/fbdcanvasview.h"
#include "views/propertypanel.h"

CMainWindow::CMainWindow(QWidget* _parent)
    : QMainWindow(_parent) {
    setWindowTitle("FBDSimulator GUI");
    resize(1280, 800);

    setupCentralLayout();
    setupMenus();
    FSimulatorBridge = new CSimulatorBridge(this);
    statusBar()->showMessage("Gotowy");
}

void CMainWindow::setupCentralLayout() {
    FMainSplitter = new QSplitter(this);

    FCanvasView = new FBDCanvasView(FMainSplitter);
    FPropertyPanel = new PropertyPanel(FMainSplitter);
    FDashboardView = new DashboardView(FMainSplitter);

    FMainSplitter->addWidget(FCanvasView);
    FMainSplitter->addWidget(FPropertyPanel);
    FMainSplitter->addWidget(FDashboardView);

    FMainSplitter->setStretchFactor(0, 5);
    FMainSplitter->setStretchFactor(1, 2);
    FMainSplitter->setStretchFactor(2, 3);

    setCentralWidget(FMainSplitter);
}

void CMainWindow::setupMenus() {
    QMenu* fileMenu = menuBar()->addMenu("Plik");
    QAction* newAction = fileMenu->addAction("Nowy");
    QAction* openAction = fileMenu->addAction("Otworz JSON...");
    QAction* saveAction = fileMenu->addAction("Zapisz JSON...");

    connect(newAction, &QAction::triggered, this, &CMainWindow::onNewScheme);
    connect(openAction, &QAction::triggered, this, &CMainWindow::onOpenScheme);
    connect(saveAction, &QAction::triggered, this, &CMainWindow::onSaveScheme);

    QMenu* simulationMenu = menuBar()->addMenu("Symulacja");
    QAction* runAction = simulationMenu->addAction("Uruchom");
    connect(runAction, &QAction::triggered, this, &CMainWindow::onRunSimulation);
}

void CMainWindow::onNewScheme() {
    FCanvasView->clearScene();
    FPropertyPanel->resetState();
    FDashboardView->appendLog("Utworzono nowy schemat.");
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

    FDashboardView->appendLog("Wybrano plik: " + path);
    statusBar()->showMessage("Wczytywanie: " + path);

    QMessageBox::information(
        this,
        "Etap implementacji",
        "Integracja z CFBDBuilder::loadFromJSON bedzie dodana w kolejnym kroku."
    );
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

    FDashboardView->appendLog("Docelowy plik zapisu: " + path);
    statusBar()->showMessage("Zapisywanie: " + path);

    QMessageBox::information(
        this,
        "Etap implementacji",
        "Integracja z CFBDBuilder::saveToJSON bedzie dodana w kolejnym kroku."
    );
}

void CMainWindow::onRunSimulation() {
    FDashboardView->appendLog("Uruchamianie domyslnej symulacji backendu...");
    const bool runOk = FSimulatorBridge->runDefaultSimulation();

    if (runOk) {
        FDashboardView->appendLog("Symulacja zakonczona.");
        statusBar()->showMessage("Symulacja zakonczona");
        return;
    }

    FDashboardView->appendLog("Nieudane uruchomienie symulacji.");
    statusBar()->showMessage("Blad uruchomienia");
}
