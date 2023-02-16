#include "HelpWidget.h"

#include "../MainWidget.h"

#include <QLabel>

HelpWidget::HelpWidget(MainWidget* mainWidget)
   : PersonaWindow(mainWidget)
{
   setCentralWidget(new QLabel("HELP"));
}

