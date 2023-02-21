#ifndef ChildrenSignalBlockerH
#define ChildrenSignalBlockerH

#include <QObject>

class ChildrenSignalBlocker
{
public:
   ChildrenSignalBlocker(QObject* object);
   ~ChildrenSignalBlocker();

private:
   QObject* object;
};

#endif // NOT ChildrenSignalBlockerH
