#ifndef HelpPatchViewH
#define HelpPatchViewH

#include <QTreeView>

namespace Help
{
   class PatchModel;

   class PatchView : public QTreeView
   {
      Q_OBJECT
   public:
      PatchView(QWidget* parent, PatchModel* model);

   private:
      PatchModel* model;
   };
} // namespace Help

#endif // NOT HelpPatchViewH
