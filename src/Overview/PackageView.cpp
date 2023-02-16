#include "PackageView.h"

Package::View::View(QWidget* parent)
   : QTreeView(parent)
{
   setHeaderHidden(true);
   //setRootIsDecorated(false);
}
