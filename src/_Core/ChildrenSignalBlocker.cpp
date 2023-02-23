#include "ChildrenSignalBlocker.h"

ChildrenSignalBlocker::ChildrenSignalBlocker(QWidget* parent)
   : parent(parent)
{
   for (QWidget* childWidget : parent->findChildren<QWidget*>(Qt::FindDirectChildrenOnly))
      childWidget->blockSignals(true);
}

ChildrenSignalBlocker::~ChildrenSignalBlocker()
{
   for (QWidget* childWidget : parent->findChildren<QWidget*>(Qt::FindDirectChildrenOnly))
      childWidget->blockSignals(false);
}
