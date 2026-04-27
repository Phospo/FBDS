#pragma once

#include <memory>

#include <QWidget>

namespace Ui {
class CanvasPanel;
}

/** CanvasPanel

    Panel otaczający widok schematu FBD i udostępniający go jako układ edytowany w Designerze.
*/
class CanvasPanel : public QWidget {
    Q_OBJECT

private:
    /** Interfejs wygenerowany z pliku .ui. */
    std::unique_ptr<Ui::CanvasPanel> FUi;

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit CanvasPanel(QWidget* _parent = nullptr);

    /**
        Destruktor domyślny.
    */
    ~CanvasPanel() override;

    /**
        Czyszczenie bieżącej sceny schematu.
    */
    void clearScene();
};