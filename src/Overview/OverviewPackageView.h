#ifndef OverviewPackageViewH
#define OverviewPackageViewH

#include "AbstractItemTreeView.h"

namespace Overview
{
   class PackageModel;

   class PackageView : public Abstract::ItemTreeView
   {
      Q_OBJECT
   public:
      PackageView(QWidget* parent, PackageModel* model);

   signals:
      void signalPatchSelected(const QString& patchPath);

   private:
      void clicked(QStandardItem* item) override;
   };
} // namespace Overview

#endif // NOT OverviewPackageViewH
