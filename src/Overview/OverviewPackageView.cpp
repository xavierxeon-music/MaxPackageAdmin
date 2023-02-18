#include "OverviewPackageView.h"

#include "OverviewPackageModel.h"

Overview::PackageView::PackageView(QWidget* parent, PackageModel* model)
   : Abstract::ItemTreeView(parent, model)
   , FunctionHub()
{
   setHeaderHidden(true);
}

void Overview::PackageView::clicked(QStandardItem* item)
{
   QVariant data = item->data(PackageModel::RolePatch);
   if (data.isNull())
      return callOnAllHubInstances(&PackageView::patchSelected, QString());

   const QString& patchPath = data.toString();
   callOnAllHubInstances(&PackageView::patchSelected, patchPath);
}
