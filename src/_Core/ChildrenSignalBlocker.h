#ifndef ChildrenSignalBlockerH
#define ChildrenSignalBlockerH

#include <QWidget>

class ChildrenSignalBlocker
{
public:
   ChildrenSignalBlocker(QWidget* parent);
   ~ChildrenSignalBlocker();

private:
   QWidget* parent;
};

#endif // NOT ChildrenSignalBlockerH
