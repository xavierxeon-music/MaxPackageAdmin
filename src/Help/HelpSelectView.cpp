#include "HelpSelectView.h"

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

void Help::SelectView::clicked(QStandardItem* item)
{
   const QVariant data = item->data(SelectModel::RolePatchPath);
   if (!data.isValid())
   {
      const QModelIndex index = item->index();
      if (isExpanded(index))
         collapse(index);
      else
         expand(index);

      return;
   }

   const QString patchPath = data.toString();
   persona->buildPatchStructure(patchPath);

   callOnAllHubInstances(&SelectView::patchSelected, patchPath);
}

void Help::SelectView::doubleClicked(QStandardItem* item)
{
   const QVariant data = item->data(SelectModel::RolePatchPath);
   if (!data.isValid())
      return;

   const QString patchPath = data.toString();
   QDesktopServices::openUrl(QUrl::fromLocalFile(patchPath));
}
