#include "HelpFileView.h"

#include "HelpFileModel.h"

Help::FileView::FileView(QWidget* parent, FileModel* model)
   : Abstract::ItemTreeView(parent, model)
{
}
