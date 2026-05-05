#pragma once

#include <memory>
#include <QString>

#include <QWidget>

#include "views/fbdcanvasview.h"

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

    /**
        Dodanie bloku do sceny.
    */
    void addBlock(const FBDCanvasView::FBDBlockData& _data);

    /**
        Wczytanie schematu z pliku JSON.
    */
    bool loadFromJson(const QString& _path);

    /**
        Zapisanie schematu do pliku JSON.
    */
    bool saveToJson(const QString& _path) const;

    /**
        Eksport bieżącego schematu do tekstu JSON.
    */
    QString exportToJson() const;

    /**
        Włączenie trybu łączenia portów.
    */
    void setConnectMode(bool _enabled);

    /**
        Usunięcie zaznaczonego elementu.
    */
    void deleteSelectedBlock();

    /**
        Zastosowanie zmiany właściwości do zaznaczonego bloku.
    */
    void setSelectedBlockProperty(const QString& _propertyName, const QString& _propertyValue);

signals:
    /**
        Zmieniono zaznaczony blok w scenie.
    */
    void blockSelected(const FBDCanvasView::FBDBlockData& blockData);
};