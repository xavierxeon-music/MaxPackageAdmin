#include "OverviewPatchView.h"

#include "OverviewPatchModel.h"

Overview::PatchView::PatchView(QWidget* parent, PatchModel* model)
   : Abstract::ItemTreeView(parent, model)
{
}
