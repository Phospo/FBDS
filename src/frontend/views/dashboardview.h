#pragma once

#include <QWidget>

class QLabel;
class QPlainTextEdit;
class QPushButton;
class QVBoxLayout;

/** DashboardView

    Panel sterowania uruchomieniem symulacji oraz podglądu logów.
*/
class DashboardView : public QWidget {
    Q_OBJECT

private:
    /** Układ panelu dashboard. */
    QVBoxLayout* FLayout{nullptr};

    /** Etykieta nagłówka sekcji. */
    QLabel* FHeaderLabel{nullptr};

    /** Przycisk uruchomienia kroku symulacji. */
    QPushButton* FRunStepButton{nullptr};

    /** Pole logów statusowych frontendu. */
    QPlainTextEdit* FLogView{nullptr};

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
};
