#include "dashboardview.h"

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

DashboardView::DashboardView(QWidget* _parent)
    : QWidget(_parent),
      FLayout(new QVBoxLayout(this)),
      FHeaderLabel(new QLabel("Dashboard symulacji", this)),
      FRunStepButton(new QPushButton("Wykonaj krok", this)),
      FLogView(new QPlainTextEdit(this)) {
    FLogView->setReadOnly(true);

    FLayout->addWidget(FHeaderLabel);
    FLayout->addWidget(FRunStepButton);
    FLayout->addWidget(FLogView);
    setLayout(FLayout);
}

void DashboardView::appendLog(const QString& _text) {
    FLogView->appendPlainText(_text);
}
