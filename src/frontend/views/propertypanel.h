#pragma once

#include <QWidget>

class QLabel;
class QTableWidget;
class QVBoxLayout;

/** PropertyPanel

    Panel prezentujący właściwości wybranego bloku FBD.
*/
class PropertyPanel : public QWidget {
    Q_OBJECT

private:
    /** Kontener układu pionowego panelu. */
    QVBoxLayout* FLayout{nullptr};

    /** Etykieta nagłówkowa panelu. */
    QLabel* FHeaderLabel{nullptr};

    /** Tabela właściwości bloku. */
    QTableWidget* FPropertiesTable{nullptr};

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
