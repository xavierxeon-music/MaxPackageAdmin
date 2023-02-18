#include "HelpPatchView.h"

#include "HelpPatchModel.h"

Help::PatchView::PatchView(QWidget* parent, PatchModel* model)
   : QTreeView(parent)
   , model(model)
{
   setModel(model);
}
