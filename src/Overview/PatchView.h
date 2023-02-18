#ifndef PatchViewH
#define PatchViewH

#include <QTreeView>

namespace Patch
{
   class View : public QTreeView
   {
      Q_OBJECT
   public:
      View(QWidget* parent);
   };
} // namespace Patch

#endif // NOT PatchViewH
