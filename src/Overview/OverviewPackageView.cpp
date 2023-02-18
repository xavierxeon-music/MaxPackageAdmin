#include "OverviewPackageView.h"

#include "OverviewPackageModel.h"

Overview::PackageView::PackageView(QWidget* parent, PackageModel* model)
   : Abstract::ItemTreeView(parent, model)
{
   setHeaderHidden(true);
}

void Overview::PackageView::clicked(QStandardItem* item)
{
   QVariant data = item->data(PackageModel::RolePatch);
   if (data.isNull())
   {
      emit signalPatchSelected(QString());
      return;
   }

   const QString& patchPath = data.toString();
   emit signalPatchSelected(patchPath);
}
