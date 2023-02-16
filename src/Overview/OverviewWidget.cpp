#include "OverviewWidget.h"

#include <QLabel>

OverviewWidget::OverviewWidget(MainWidget* mainWidget)
   : PersonaWindow(mainWidget)
{
   setCentralWidget(new QLabel("OVERVIEW"));
}

