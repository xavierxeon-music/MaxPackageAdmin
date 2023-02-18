#include "AbstractItemTreeView.h"

Abstract::ItemTreeView::ItemTreeView(QWidget* parent, QStandardItemModel* model)
   : QTreeView(parent)
   , model(model)
{
   setModel(model);
   connect(this, &QAbstractItemView::clicked, this, &ItemTreeView::slotClicked);
   connect(this, &QAbstractItemView::doubleClicked, this, &ItemTreeView::slotDoubleClicked);

   connect(model, &QAbstractItemModel::modelReset, this, &ItemTreeView::slotResizeAllColumns);
   connect(this, &QTreeView::expanded, this, &ItemTreeView::slotResizeAllColumns);
   connect(this, &QTreeView::collapsed, this, &ItemTreeView::slotResizeAllColumns);
}

void Abstract::ItemTreeView::clicked(QStandardItem* item)
{
   // do nothing
   Q_UNUSED(item)
}

void Abstract::ItemTreeView::doubleClicked(QStandardItem* item)
{
   // do nothing
   Q_UNUSED(item)
}

void Abstract::ItemTreeView::slotClicked(const QModelIndex& index)
{
   QStandardItem* item = model->itemFromIndex(index);
   clicked(item);
}

void Abstract::ItemTreeView::slotDoubleClicked(const QModelIndex& index)
{
   QStandardItem* item = model->itemFromIndex(index);
   doubleClicked(item);
}

void Abstract::ItemTreeView::slotResizeAllColumns()
{
   resizeColumnToContents(0);
}
