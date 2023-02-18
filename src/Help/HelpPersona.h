#ifndef HelpPersonaH
#define HelpPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>

namespace Help
{
   class SelectModel;
   class PatchModel;
   class FileModel;

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

   private:
      SelectModel* selectModel;
      PatchModel* patchModel;
      FileModel* fileModel;
   };
} // namespace Help

#endif // NOT HelpPersonaH
