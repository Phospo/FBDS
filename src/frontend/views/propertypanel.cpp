#include "propertypanel.h"

#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>

PropertyPanel::PropertyPanel(QWidget* _parent)
    : QWidget(_parent),
      FLayout(new QVBoxLayout(this)),
      FHeaderLabel(new QLabel("Wlasciwosci bloku", this)),
      FPropertiesTable(new QTableWidget(this)) {
    FPropertiesTable->setColumnCount(2);
    FPropertiesTable->setHorizontalHeaderLabels({"Parametr", "Wartosc"});
    FPropertiesTable->horizontalHeader()->setStretchLastSection(true);

    FLayout->addWidget(FHeaderLabel);
    FLayout->addWidget(FPropertiesTable);
    setLayout(FLayout);
}

void PropertyPanel::resetState() {
    FPropertiesTable->clearContents();
    FPropertiesTable->setRowCount(0);
}
