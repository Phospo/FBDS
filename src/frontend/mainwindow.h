#pragma once

#include <QMainWindow>

class FBDCanvasView;
class PropertyPanel;
class DashboardView;
class CSimulatorBridge;
class QSplitter;

/** CMainWindow

    Główne okno aplikacji frontendowej symulatora FBD.
*/
class CMainWindow : public QMainWindow {
    Q_OBJECT

private:
    /** Główny podział przestrzeni roboczej okna. */
    QSplitter* FMainSplitter{nullptr};

    /** Widok schematu FBD. */
    FBDCanvasView* FCanvasView{nullptr};

    /** Panel właściwości zaznaczonego elementu. */
    PropertyPanel* FPropertyPanel{nullptr};

    /** Panel sterowania i podglądu wyników symulacji. */
    DashboardView* FDashboardView{nullptr};

    /** Most łączący frontend z backendem symulatora. */
    CSimulatorBridge* FSimulatorBridge{nullptr};

    /**
        Budowa układu centralnego okna.
    */
    void setupCentralLayout();

    /**
        Budowa menu aplikacji.
    */
    void setupMenus();

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

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit CMainWindow(QWidget* _parent = nullptr);
};
