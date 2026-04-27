#include "propertypanel.h"

#include "ui_propertypanel.h"

#include <QHeaderView>

PropertyPanel::PropertyPanel(QWidget* _parent)
  : QWidget(_parent), FUi(std::make_unique<Ui::PropertyPanel>()) {
  FUi->setupUi(this);

  FUi->propertiesTable->setColumnCount(2);
  FUi->propertiesTable->setHorizontalHeaderLabels({"Parametr", "Wartosc"});
  FUi->propertiesTable->horizontalHeader()->setStretchLastSection(true);
}

void PropertyPanel::resetState() {
  FUi->propertiesTable->clearContents();
  FUi->propertiesTable->setRowCount(0);
}
