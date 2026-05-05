#pragma once

#include <memory>
#include <QMap>
#include <QString>
#include <QTableWidgetItem>
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
    bool FUpdating{false};

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

    /**
        Ustawienie właściwości aktualnie wybranego bloku.

        @param _properties Mapa par nazwa/wartość
    */
    void setProperties(const QMap<QString, QString>& _properties);

    /**
        Wyczyść panel właściwości.
    */
    void clearProperties();

signals:
    /**
        Zmieniono wartość właściwości przez użytkownika.
    */
    void propertyValueChanged(const QString& propertyName, const QString& propertyValue);

private slots:
    void onTableItemChanged(QTableWidgetItem* item);
};
