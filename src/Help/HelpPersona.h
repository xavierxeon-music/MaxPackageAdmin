#ifndef HelpPersonaH
#define HelpPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>

#include <Central.h>

#include "HelpPatchStructure.h"

namespace Help
{
   class SelectModel;
   class ComponentsModel;

   class Persona : public Abstract::Persona,
                   private Central::FunctionHub
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
      const QString& getCurrentKey() const;
      PatchStructure structure() const;
      PatchStructure& structureRef();
      void savePatchStructures();
      void buildPatchStructure(QString patchPath, const QString& key);

   private:
      using StructureMap = QMap<QString, PatchStructure>;

   private slots:
      void slotReload();
      void slotSave();

   private:
      SelectModel* selectModel;
      ComponentsModel* componentsModel;
      QString currentKey;
      StructureMap structureMap;
   };
} // namespace Help

#endif // NOT HelpPersonaH
