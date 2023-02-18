#include "HelpSelectView.h"

#include "HelpSelectModel.h"

Help::SelectView::SelectView(QWidget* parent, SelectModel* model)
   : Abstract::ItemTreeView(parent, model)
   , Persona::FunctionHub()
{
}

void Help::SelectView::clicked(QStandardItem* item)
{
   const QString patchPath = item->data(SelectModel::RolePatchPath).toString();
   const QString helpPath = item->data(SelectModel::RoleHelpPath).toString();

   callOnAllHubInstances(&SelectView::patchSelected, patchPath, helpPath);
}
