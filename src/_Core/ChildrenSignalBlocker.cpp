#include "ChildrenSignalBlocker.h"

ChildrenSignalBlocker::ChildrenSignalBlocker(QObject* object)
   : object(object)
{
   for (QObject* childObject : object->findChildren<QObject*>())
      childObject->blockSignals(true);
}

ChildrenSignalBlocker::~ChildrenSignalBlocker()
{
   for (QObject* childObject : object->findChildren<QObject*>())
      childObject->blockSignals(false);
}
