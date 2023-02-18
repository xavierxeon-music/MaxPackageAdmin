#include "HelpPatchView.h"

#include "HelpPatchModel.h"

Help::PatchView::PatchView(QWidget* parent, PatchModel* model)
   : Abstract::ItemTreeView(parent, model)
{
}
