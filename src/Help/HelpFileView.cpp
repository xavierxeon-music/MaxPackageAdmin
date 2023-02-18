#include "HelpFileView.h"

#include "HelpFileModel.h"

Help::FileView::FileView(QWidget* parent, FileModel* model)
   : QTreeView(parent)
   , model(model)
{
   setModel(model);
}
