#include "PatchRawView.h"

#include "PatchRawModel.h"

Patch::RawView::RawView(QWidget* parent, RawModel* model)
   : QTreeView(parent)
   , model(model)
{
   connect(model, &RawModel::signalUpdated, this, &RawView::slotResizeAllColumns);
   connect(this, &QTreeView::expanded, this, &RawView::slotResizeAllColumns);
   connect(this, &QTreeView::collapsed, this, &RawView::slotResizeAllColumns);

   setModel(model);
}

void Patch::RawView::slotResizeAllColumns()
{
   resizeColumnToContents(0);
}
