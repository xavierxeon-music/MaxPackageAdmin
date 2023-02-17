#include "HelpWidget.h"

#include "../MainWidget.h"

HelpWidget::HelpWidget(MainWidget* mainWidget)
   : PersonaWindow(mainWidget, "HELP")
{
   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload");
}
