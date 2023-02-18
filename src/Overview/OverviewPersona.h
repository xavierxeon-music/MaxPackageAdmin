#ifndef OverviewPersonaH
#define OverviewPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>
#include <Central.h>

namespace Overview
{
   class PackageModel;
   class PatchModel;

   class Persona : public Abstract::Persona, private Central::FunctionHub
   {
      Q_OBJECT

   public:
      struct FunctionHub : public Abstract::FunctionHub<Persona>
      {
         virtual void patchSelected(QString patchPath);
      };

   public:
      Persona(MainWidget* mainWidget);

   private slots:
      void slotOpenPackage();

   private:
      PackageModel* packageModel;
      PatchModel* patchModel;
   };

} // namespace Overview

#endif // NOT OverviewPersonaH
