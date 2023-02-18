#ifndef OverviewPackageViewH
#define OverviewPackageViewH

#include "OverviewPersona.h"
#include <AbstractItemTreeView.h>

namespace Overview
{
   class PackageModel;

   class PackageView : public Abstract::ItemTreeView,
                       private Persona::FunctionHub
   {
      Q_OBJECT
   public:
      PackageView(QWidget* parent, PackageModel* model);

   private:
      void clicked(QStandardItem* item) override;
   };
} // namespace Overview

#endif // NOT OverviewPackageViewH
