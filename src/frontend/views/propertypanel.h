#pragma once

#include <memory>

#include <QWidget>

namespace Ui {
class PropertyPanel;
}

/** PropertyPanel

    Panel prezentujący właściwości wybranego bloku FBD.
*/
class PropertyPanel : public QWidget {
    Q_OBJECT

private:
    /** Interfejs wygenerowany z pliku .ui. */
    std::unique_ptr<Ui::PropertyPanel> FUi;

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit PropertyPanel(QWidget* _parent = nullptr);

    /**
        Resetowanie zawartości panelu do stanu początkowego.
    */
    void resetState();
};
