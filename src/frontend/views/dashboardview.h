#pragma once

#include <memory>

#include <QWidget>

namespace Ui {
class DashboardView;
}

/** DashboardView

    Panel sterowania uruchomieniem symulacji oraz podglądu logów.
*/
class DashboardView : public QWidget {
    Q_OBJECT

private:
    /** Interfejs wygenerowany z pliku .ui. */
    std::unique_ptr<Ui::DashboardView> FUi;

signals:
    /**
        Zgłoszenie żądania wykonania pojedynczego kroku symulacji.
    */
    void runStepRequested();

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit DashboardView(QWidget* _parent = nullptr);

    /**
        Dopisanie komunikatu do panelu logów.

        @param _text Tekst komunikatu
    */
    void appendLog(const QString& _text);

    /**
        Dopisanie komunikatu do panelu wyjścia symulacji.

        @param _text Tekst komunikatu
    */
    void appendSimulationOutput(const QString& _text);
};
