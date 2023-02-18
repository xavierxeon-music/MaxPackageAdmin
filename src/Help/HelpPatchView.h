#ifndef HelpPatchViewH
#define HelpPatchViewH

#include <AbstractItemTreeView.h>

namespace Help
{
   class PatchModel;

   class PatchView : public Abstract::ItemTreeView
   {
      Q_OBJECT
   public:
      PatchView(QWidget* parent, PatchModel* model);
   };
} // namespace Help

#endif // NOT HelpPatchViewH
