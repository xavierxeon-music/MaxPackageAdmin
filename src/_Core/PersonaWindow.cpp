#include "PersonaWindow.h"

#include "MainWidget.h"

PersonaWindow::PersonaWindow(MainWidget* mainWidget, const QString& name)
   : QWidget(mainWidget)
   , mainWidget(mainWidget)
   , name(name)
   , toolBar(nullptr)
{
   toolBar = new QToolBar(mainWidget);

   mainWidget->addPersona(this, toolBar, name);
}

QToolBar* PersonaWindow::getToolBar()
{
   return toolBar;
}
