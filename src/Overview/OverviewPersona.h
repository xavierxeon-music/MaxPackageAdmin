#ifndef OverviewPersonaH
#define OverviewPersonaH

#include <AbstractPersona.h>

#include "OverviewPackageModel.h"
#include "OverviewPatchModel.h"

namespace Overview
{
   class Persona : public Abstract::Persona
   {
      Q_OBJECT
   public:
      Persona(MainWidget* mainWidget);

   signals:
      void signalUpdateTitle();

   private slots:
      void slotOpenPackage();

   private:
      PackageModel* packageModel;
      PatchModel* patchModel;
   };
} // namespace Overview

#endif // NOT OverviewPersonaH
