#include "HelpSelectView.h"

#include <QDesktopServices>
#include <QUrl>

#include "HelpSelectModel.h"

Help::SelectView::SelectView(QWidget* parent, SelectModel* model)
   : Abstract::ItemTreeView(parent, model)
   , Persona::FunctionHub()
{
   setHeaderHidden(true);
   setRootIsDecorated(false);
}

void Help::SelectView::clicked(QStandardItem* item)
{
   const QString patchPath = item->data(SelectModel::RolePatchPath).toString();

   callOnAllHubInstances(&SelectView::patchSelected, patchPath);
}

void Help::SelectView::doubleClicked(QStandardItem* item)
{
   const QString patchPath = item->data(SelectModel::RolePatchPath).toString();
   QDesktopServices::openUrl(QUrl::fromLocalFile(patchPath));
}
