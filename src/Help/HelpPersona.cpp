#include "HelpPersona.h"

#include "../MainWidget.h"

HelpPersona::HelpPersona(MainWidget* mainWidget)
   : Persona(mainWidget, "HELP")
{
   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload");
}
