#ifndef OverviewPatchModelH
#define OverviewPatchModelH

#include "OverviewPersona.h"
#include <JSONModel.h>

namespace Overview
{
   class PatchModel : public JSON::Model,
                      private Persona::FunctionHub
   {
      Q_OBJECT

   public:
      PatchModel(QObject* parent);

   private:
      void patchSelected(QString patchPath) override;
   };
} // namespace Overview

#endif // NOT OverviewPatchModelH
