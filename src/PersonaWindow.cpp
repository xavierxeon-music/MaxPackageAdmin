#include "PersonaWindow.h"

#include "MainWidget.h"

PersonaWindow::PersonaWindow(MainWidget* mainWidget)
   : QMainWindow(mainWidget)
   , mainWidget(mainWidget)
{
}

