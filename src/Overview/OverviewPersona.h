#ifndef OverviewPersonaH
#define OverviewPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>

namespace Overview
{
   class Persona;
   class PackageModel;
   class PatchModel;

   class FunctionHub : public Abstract::FunctionHub<Persona>
   {
   public:
      FunctionHub();

   protected:
      virtual void patchSelected(QString patchPath);
   };

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
