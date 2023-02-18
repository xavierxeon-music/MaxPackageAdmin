#include "AbstractPersona.h"

#include "MainWidget.h"

QList<Abstract::Persona*> Abstract::Persona::personaList;

Abstract::Persona::Persona(MainWidget* mainWidget, const QString& name)
   : QWidget(mainWidget)
   , mainWidget(mainWidget)
   , name(name)
   , toolBar(nullptr)
{
   personaList.append(this);

   toolBar = new QToolBar(mainWidget);
   toolBar->setMovable(false);

   const int index = mainWidget->centralStackWidget->addWidget(this);
   mainWidget->tabToolBar->addTab(index, name);

   mainWidget->addToolBar(toolBar);
   mainWidget->toolBarMap[index] = toolBar;
}

void Abstract::Persona::initAll()
{
   for (Persona* persona : personaList)
      persona->init();
}

Abstract::Persona::~Persona()
{
   personaList.removeAll(this);
}

void Abstract::Persona::init()
{
   // do nothing
}

QToolBar* Abstract::Persona::getToolBar()
{
   return toolBar;
}
