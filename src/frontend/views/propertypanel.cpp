#include "propertypanel.h"

#include "ui_propertypanel.h"

#include <QHeaderView>

PropertyPanel::PropertyPanel(QWidget* _parent)
  : QWidget(_parent), FUi(std::make_unique<Ui::PropertyPanel>()) {
  FUi->setupUi(this);

  FUi->propertiesTable->setColumnCount(2);
  FUi->propertiesTable->setHorizontalHeaderLabels({"Parametr", "Wartosc"});
  FUi->propertiesTable->horizontalHeader()->setStretchLastSection(true);

  connect(FUi->propertiesTable, &QTableWidget::itemChanged, this, &PropertyPanel::onTableItemChanged);
}

void PropertyPanel::resetState() {
  FUi->propertiesTable->clearContents();
  FUi->propertiesTable->setRowCount(0);
}

void PropertyPanel::setProperties(const QMap<QString, QString>& _properties) {
  FUpdating = true;
  FUi->propertiesTable->clearContents();
  FUi->propertiesTable->setRowCount(_properties.size());

  int row = 0;
  for (auto it = _properties.constBegin(); it != _properties.constEnd(); ++it, ++row) {
    auto* keyItem = new QTableWidgetItem(it.key());
    keyItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    auto* valueItem = new QTableWidgetItem(it.value());
    if (it.key() == "Type") {
      valueItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
    FUi->propertiesTable->setItem(row, 0, keyItem);
    FUi->propertiesTable->setItem(row, 1, valueItem);
  }

  FUpdating = false;
}

void PropertyPanel::clearProperties() {
  FUpdating = true;
  FUi->propertiesTable->clearContents();
  FUi->propertiesTable->setRowCount(0);
  FUpdating = false;
}

void PropertyPanel::onTableItemChanged(QTableWidgetItem* item) {
  if (FUpdating || item == nullptr || item->column() != 1) {
    return;
  }

  const int row = item->row();
  const QTableWidgetItem* keyItem = FUi->propertiesTable->item(row, 0);
  if (keyItem == nullptr) {
    return;
  }

  const QString propertyName = keyItem->text();
  const QString propertyValue = item->text();
  emit propertyValueChanged(propertyName, propertyValue);
}
