#pragma once

#include <memory>

#include <QMainWindow>

#include "views/fbdcanvasview.h"

class CSimulatorBridge;

namespace Ui {
class MainWindow;
}

/** CMainWindow

    Główne okno aplikacji frontendowej symulatora FBD.
*/
class CMainWindow : public QMainWindow {
    Q_OBJECT

private:
    /** Interfejs wygenerowany z pliku .ui dla głównego okna. */
    std::unique_ptr<Ui::MainWindow> FUi;

    /** Most łączący frontend z backendem symulatora. */
    CSimulatorBridge* FSimulatorBridge{nullptr};

private slots:
    /**
        Obsługa utworzenia nowego schematu.
    */
    void onNewScheme();

    /**
        Obsługa otwarcia schematu z pliku JSON.
    */
    void onOpenScheme();

    /**
        Obsługa zapisu schematu do pliku JSON.
    */
    void onSaveScheme();

    /**
        Uruchomienie symulacji.
    */
    void onRunSimulation();

    /**
        Utworzenie nowego bloku na scenie.
    */
    void onAddBlock();

    /**
        Usuwanie zaznaczonego bloku.
    */
    void onDeleteSelected();

    /**
        Zmiana właściwości zaznaczonego bloku.
    */
    void onPropertyValueChanged(const QString& propertyName, const QString& propertyValue);

    /**
        Aktualizacja panelu właściwości po wybraniu bloku.
    */
    void onBlockSelected(const FBDCanvasView::FBDBlockData& blockData);

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit CMainWindow(QWidget* _parent = nullptr);
    
    /**
        Destruktor domyślny.
    */
    ~CMainWindow() override;
};
