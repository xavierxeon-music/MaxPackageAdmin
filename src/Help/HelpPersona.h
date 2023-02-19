#ifndef HelpPersonaH
#define HelpPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>

#include "HelpPatchStructure.h"

namespace Help
{
   class SelectModel;
   class ComponentsModel;

   class Persona : public Abstract::Persona
   {
      Q_OBJECT

   public:
      struct FunctionHub : public Abstract::FunctionHub<Persona>
      {
         virtual void patchSelected(QString patchPath);
      };

   public:
      Persona(MainWidget* mainWidget);

   public:
      void buildPatchStructure(QString patchPath);
      PatchStructure* patchStructureRef();

   private:
      SelectModel* selectModel;
      ComponentsModel* componentsModel;

      PatchStructure patchStructure;
   };
} // namespace Help

#endif // NOT HelpPersonaH
