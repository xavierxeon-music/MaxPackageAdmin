#include "HelpComponentsView.h"

#include "HelpComponentsModel.h"

Help::ComponentsView::ComponentsView(QWidget* parent, ComponentsModel* model)
   : Abstract::ItemTreeView(parent, model)
{
}
