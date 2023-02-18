#include "PackageView.h"

#include "PackageModel.h"

Package::View::View(QWidget* parent, Model* model)
   : Abstract::ItemTreeView(parent, model)
{
   setHeaderHidden(true);
}

void Package::View::clicked(QStandardItem* item)
{
   QVariant data = item->data(Model::RolePatch);
   if (data.isNull())
   {
      emit signalPatchSelected(QString());
      return;
   }

   const QString& patchPath = data.toString();
   emit signalPatchSelected(patchPath);
}
