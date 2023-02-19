#include "AbstractPersona.h"

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

#include "MainWidget.h"
#include "Settings.h"

QList<Abstract::Persona*> Abstract::Persona::personaList;

Abstract::Persona::Persona(MainWidget* mainWidget, const QString& name)
   : QWidget(mainWidget)
   , mainWidget(mainWidget)
   , name(name)
   , toolBar(nullptr)
   , splitter(nullptr)
{
   personaList.append(this);

   toolBar = new QToolBar(mainWidget);
   toolBar->setMovable(false);

   const int index = mainWidget->centralStackWidget->addWidget(this);
   mainWidget->tabToolBar->addTab(index, name);

   mainWidget->addToolBar(toolBar);
   mainWidget->toolBarMap[index] = toolBar;

   splitter = new QSplitter(this);

   QVBoxLayout* mainLayout = new QVBoxLayout(this);
   mainLayout->setContentsMargins(0, 0, 0, 0);
   mainLayout->addWidget(splitter);
}

void Abstract::Persona::callOnAllInstances(void (Persona::*functionPointer)())
{
   for (Persona* persona : personaList)
   {
      (persona->*functionPointer)();
   }
}

Abstract::Persona::~Persona()
{
   personaList.removeAll(this);
}

void Abstract::Persona::laodState()
{
   Settings personaSettings("Persona_" + name);
   const QByteArray splitterState = personaSettings.bytes("Splitter");
   splitter->restoreState(splitterState);
}

void Abstract::Persona::saveState()
{
   Settings personaSettings("Persona_" + name);
   personaSettings.write("Splitter", splitter->saveState());
}

QToolBar* Abstract::Persona::getToolBar()
{
   return toolBar;
}

void Abstract::Persona::addWidget(QWidget* widget, const QString& title)
{
   QWidget* container = new QWidget(this);
   QLabel* titleLabel = new QLabel(title, this);

   QGridLayout* containerLayout = new QGridLayout(container);
   containerLayout->setContentsMargins(0, 0, 0, 0);
   containerLayout->addWidget(titleLabel, 0, 0);
   containerLayout->addWidget(widget, 1, 0);

   splitter->addWidget(container);
}
