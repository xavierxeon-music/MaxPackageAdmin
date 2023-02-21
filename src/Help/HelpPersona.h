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
         virtual void patchSelected(QString patchPath, QString key);
         virtual void componentSelected(PatchStructure::Marker marker, QVariant data);
      };

   public:
      Persona(MainWidget* mainWidget);

   public:
      PatchStructure* patchStructureRef(const QString& key);

      void savePatchStructures();
      void buildPatchStructure(QString patchPath, const QString& key);

   private:
      using StructureMap = QMap<QString, PatchStructure>;

   private:
      SelectModel* selectModel;
      ComponentsModel* componentsModel;
      StructureMap structureMap;
   };
} // namespace Help

#endif // NOT HelpPersonaH
