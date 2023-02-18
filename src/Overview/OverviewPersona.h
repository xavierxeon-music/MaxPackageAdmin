#ifndef OverviewPersonaH
#define OverviewPersonaH

#include <AbstractPersona.h>

#include "PackageModel.h"
#include "PatchRawModel.h"

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
      Package::Model* packageModel;
      Patch::RawModel* patchRawModel;
   };
} // namespace Overview

#endif // NOT OverviewPersonaH
