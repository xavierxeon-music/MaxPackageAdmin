#include "PackageView.h"

#include "PackageModel.h"

Package::View::View(QWidget* parent, Model* model)
   : QTreeView(parent)
   , model(model)
{
   setHeaderHidden(true);
   connect(this, &QAbstractItemView::clicked, this, &View::slotClicked);

   setModel(model);
}

void Package::View::slotClicked(const QModelIndex& index)
{
   QStandardItem* item = model->itemFromIndex(index);
   QVariant data = item->data(Model::RolePatch);
   if (data.isNull())
   {
      emit signalPatchSelected(QString());
      return;
   }

   const QString& patchPath = data.toString();
   emit signalPatchSelected(patchPath);
}
