#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTemporaryFile>
#include <QMap>

#include "simulatorbridge.h"
#include "views/dashboardview.h"

CMainWindow::CMainWindow(QWidget* _parent)
    : QMainWindow(_parent), FUi(std::make_unique<Ui::MainWindow>()), FSimulatorBridge(new CSimulatorBridge(this)) {
    FUi->setupUi(this);

    FUi->mainSplitter->setStretchFactor(0, 1);
    FUi->mainSplitter->setStretchFactor(1, 2);
    FUi->mainSplitter->setStretchFactor(2, 2);

    connect(FUi->actionNewScheme, &QAction::triggered, this, &CMainWindow::onNewScheme);
    connect(FUi->actionOpenScheme, &QAction::triggered, this, &CMainWindow::onOpenScheme);
    connect(FUi->actionSaveScheme, &QAction::triggered, this, &CMainWindow::onSaveScheme);
    connect(FUi->actionRunSimulation, &QAction::triggered, this, &CMainWindow::onRunSimulation);
    connect(FUi->dashboardView, &DashboardView::runStepRequested, this, &CMainWindow::onRunSimulation);
    connect(FUi->canvasPanel, &CanvasPanel::blockSelected, this, &CMainWindow::onBlockSelected);
    connect(FUi->propertyPanel, &PropertyPanel::propertyValueChanged, this, &CMainWindow::onPropertyValueChanged);
    connect(FUi->canvasPanel, &CanvasPanel::addBlockRequested, this, &CMainWindow::onAddBlock);
    connect(FUi->canvasPanel, &CanvasPanel::deleteSelectedRequested, this, &CMainWindow::onDeleteSelected);

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

    const bool viewOk = FUi->canvasPanel->loadFromJson(path);
    const bool backendOk = FSimulatorBridge->loadConfigurationFromJSON(path);
    if (viewOk && backendOk) {
        FUi->dashboardView->appendLog("Konfiguracja JSON zostala wczytana.");
        statusBar()->showMessage("Wczytano konfiguracje JSON");
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

    const bool saveOk = FUi->canvasPanel->saveToJson(path);
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

void CMainWindow::onAddBlock() {
    const QString blockType = QInputDialog::getItem(
        this,
        "Typ bloku",
        "Wybierz typ bloku:",
        {"SinGen", "ConstVal", "FunctionBlock"},
        0,
        false
    );

    if (blockType.isEmpty()) {
        return;
    }

    QString name = QInputDialog::getText(this, "Nazwa bloku", "Podaj nazwe bloku:", QLineEdit::Normal, blockType + "1");
    if (name.isEmpty()) {
        return;
    }

    FBDCanvasView::FBDBlockData data;
    data.Type = blockType;
    data.Name = name;

    if (blockType == "SinGen") {
        data.Frequency = QInputDialog::getDouble(this, "SinGen", "Czestotliwosc:", 1.0, 0.0, 1000.0, 2);
        data.Amplitude = QInputDialog::getDouble(this, "SinGen", "Amplituda:", 1.0, -1000.0, 1000.0, 2);
        data.Phase = QInputDialog::getDouble(this, "SinGen", "Faza:", 0.0, -360.0, 360.0, 2);
        data.Offset = QInputDialog::getDouble(this, "SinGen", "Przesuniecie:", 0.0, -1000.0, 1000.0, 2);
        data.RoundingPrecision = QInputDialog::getInt(this, "SinGen", "Precyzja zaokraglenia:", 6, -1, 12);
    } else if (blockType == "ConstVal") {
        data.ConstValue = QInputDialog::getDouble(this, "ConstVal", "Wartosc stala:", 1.0, -100000.0, 100000.0, 2);
    } else {
        data.InputCount = static_cast<unsigned>(QInputDialog::getInt(this, "FunctionBlock", "Liczba wejsc:", 2, 1, 8));
        data.ConstValue = QInputDialog::getDouble(this, "FunctionBlock", "Wartosc stala:", 0.0, -100000.0, 100000.0, 2);
        data.InitialOutput = QInputDialog::getDouble(this, "FunctionBlock", "Wyjsciowa wartosc poczatkowa:", 0.0, -100000.0, 100000.0, 2);
    }

    FUi->canvasPanel->addBlock(data);
    statusBar()->showMessage("Dodano blok: " + data.Name);
}

void CMainWindow::onDeleteSelected() {
    FUi->canvasPanel->deleteSelectedBlock();
    FUi->propertyPanel->clearProperties();
    statusBar()->showMessage("Usunieto zaznaczony blok.");
}

void CMainWindow::onPropertyValueChanged(const QString& propertyName, const QString& propertyValue) {
    FUi->canvasPanel->setSelectedBlockProperty(propertyName, propertyValue);
}

void CMainWindow::onBlockSelected(const FBDCanvasView::FBDBlockData& blockData) {
    if (blockData.Name.isEmpty()) {
        FUi->propertyPanel->clearProperties();
        return;
    }

    QMap<QString, QString> properties;
    properties.insert("Name", blockData.Name);
    properties.insert("Type", blockData.Type);
    properties.insert("InputCount", QString::number(blockData.InputCount));
    if (blockData.Type == "SinGen") {
        properties.insert("Frequency", QString::number(blockData.Frequency));
        properties.insert("Amplitude", QString::number(blockData.Amplitude));
        properties.insert("Phase", QString::number(blockData.Phase));
        properties.insert("Offset", QString::number(blockData.Offset));
        properties.insert("RoundingPrecision", QString::number(blockData.RoundingPrecision));
    } else if (blockData.Type == "ConstVal") {
        properties.insert("ConstValue", QString::number(blockData.ConstValue));
    } else {
        properties.insert("ConstValue", QString::number(blockData.ConstValue));
        properties.insert("InitialOutput", QString::number(blockData.InitialOutput));
    }

    FUi->propertyPanel->setProperties(properties);
}

void CMainWindow::onRunSimulation() {
    FUi->dashboardView->appendLog("Przygotowywanie bieżącego schematu do symulacji...");
    const QString sceneJson = FUi->canvasPanel->exportToJson();
    if (sceneJson.trimmed().isEmpty()) {
        FUi->dashboardView->appendLog("Brak schematu do uruchomienia.");
        statusBar()->showMessage("Brak schematu");
        return;
    }

    QTemporaryFile tempFile;
    if (!tempFile.open()) {
        FUi->dashboardView->appendLog("Nieudane utworzenie tymczasowego pliku JSON.");
        statusBar()->showMessage("Blad tymczasowego pliku");
        return;
    }

    tempFile.write(sceneJson.toUtf8());
    tempFile.close();

    if (!FSimulatorBridge->loadConfigurationFromJSON(tempFile.fileName())) {
        FUi->dashboardView->appendLog("Nieudane wczytanie konfiguracji do backendu.");
        statusBar()->showMessage("Blad backendu");
        QMessageBox::warning(this, "Symulacja", "Nie udalo sie wczytac konfiguracji do symulatora.");
        return;
    }

    FUi->dashboardView->appendLog("Uruchamianie symulacji...");
    const QString simulationOutput = FSimulatorBridge->runDefaultSimulationWithOutput();
    const bool runOk = !simulationOutput.isNull();

    if (runOk) {
        if (!simulationOutput.trimmed().isEmpty()) {
            FUi->dashboardView->appendSimulationOutput(simulationOutput.trimmed());
        }
        FUi->dashboardView->appendLog("Symulacja zakonczona.");
        statusBar()->showMessage("Symulacja zakonczona");
        return;
    }

    FUi->dashboardView->appendLog("Nieudane uruchomienie symulacji.");
    statusBar()->showMessage("Blad uruchomienia");
}
