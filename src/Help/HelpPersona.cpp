#include "HelpPersona.h"

#include "../MainWidget.h"

Help::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "HELP")
{
   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload");
}
