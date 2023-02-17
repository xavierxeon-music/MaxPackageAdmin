#include "PersonaWindow.h"

#include "MainWidget.h"

#include <QDockWidget>

PersonaWindow::PersonaWindow(MainWidget* mainWidget)
   : QMainWindow(mainWidget)
   , mainWidget(mainWidget)
{
}

void PersonaWindow::setLeftDock(QWidget* payload)
{
   QDockWidget* packageDock = new QDockWidget(this);
   packageDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
   packageDock->setTitleBarWidget(new QWidget());

   packageDock->setWidget(payload);
   addDockWidget(Qt::LeftDockWidgetArea, packageDock);
}
