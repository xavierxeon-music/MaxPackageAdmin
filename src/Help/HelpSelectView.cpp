#include "HelpSelectView.h"

#include "HelpSelectModel.h"

Help::SelectView::SelectView(QWidget* parent, SelectModel* model)
   : QTreeView(parent)
   , model(model)
{
   setModel(model);
}
