#ifndef OverviewPatchViewH
#define OverviewPatchViewH

#include <AbstractItemTreeView.h>

namespace Overview
{
   class PatchModel;

   class PatchView : public Abstract::ItemTreeView
   {
      Q_OBJECT
   public:
      PatchView(QWidget* parent, PatchModel* model);
   };
} // namespace Overview

#endif // NOT OverviewPatchViewH
