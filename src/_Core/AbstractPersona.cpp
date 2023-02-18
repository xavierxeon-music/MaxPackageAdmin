#include "AbstractPersona.h"

#include "MainWidget.h"

Abstract::Persona::Persona(MainWidget* mainWidget, const QString& name)
   : QWidget(mainWidget)
   , mainWidget(mainWidget)
   , name(name)
   , toolBar(nullptr)
{
   toolBar = new QToolBar(mainWidget);
   toolBar->setMovable(false);

   const int index = mainWidget->centralStackWidget->addWidget(this);
   mainWidget->tabToolBar->addTab(index, name);

   mainWidget->addToolBar(toolBar);
   mainWidget->toolBarMap[index] = toolBar;
}

QToolBar* Abstract::Persona::getToolBar()
{
   return toolBar;
}
