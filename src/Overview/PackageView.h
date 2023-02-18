#ifndef PackageViewH
#define PackageViewH

#include "AbstractItemTreeView.h"

namespace Package
{
   class Model;

   class View : public Abstract::ItemTreeView
   {
      Q_OBJECT
   public:
      View(QWidget* parent, Model* model);

   signals:
      void signalPatchSelected(const QString& patchPath);

   private:
      void clicked(QStandardItem* item) override;
   };
} // namespace Package

#endif // NOT PackageViewH
