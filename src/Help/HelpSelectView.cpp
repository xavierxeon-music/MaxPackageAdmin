#include "HelpSelectView.h"

#include <QApplication>
#include <QDesktopServices>
#include <QUrl>

#include "HelpSelectModel.h"

Help::SelectView::SelectView(Persona* persona, SelectModel* model)
   : Abstract::ItemTreeView(persona, model)
   , Persona::FunctionHub()
   , persona(persona)
{
   setHeaderHidden(true);
}

void Help::SelectView::clicked(ModelItem* item)
{
   const QVariant data = item->data(SelectModel::RolePatchPath);
   if (!data.isValid())
      return;

   const QString patchPath = data.toString();

   QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
   persona->buildPatchStructure(patchPath);
   QApplication::restoreOverrideCursor();

   callOnAllHubInstances(&SelectView::patchSelected, patchPath);
}

void Help::SelectView::doubleClicked(ModelItem* item)
{
   const QVariant data = item->data(SelectModel::RolePatchPath);
   if (!data.isValid())
      return;

   const QString patchPath = data.toString();
   QDesktopServices::openUrl(QUrl::fromLocalFile(patchPath));
}
