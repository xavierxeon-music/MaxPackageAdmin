#ifndef HelpPersonaH
#define HelpPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>

#include "HelpPatchStructure.h"

namespace Help
{
   class SelectModel;
   class ComponentsModel;
   class FileModel;

   class Persona : public Abstract::Persona
   {
      Q_OBJECT

   public:
      struct FunctionHub : public Abstract::FunctionHub<Persona>
      {
         virtual void patchSelected(QString patchPath);

         PatchStructure patchStructure;
      };

   public:
      Persona(MainWidget* mainWidget);

   private:
      SelectModel* selectModel;
      ComponentsModel* componentsModel;
      FileModel* fileModel;
   };
} // namespace Help

#endif // NOT HelpPersonaH
