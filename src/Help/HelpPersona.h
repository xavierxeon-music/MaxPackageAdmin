#ifndef HelpPersonaH
#define HelpPersonaH

#include <AbstractFunctionHub.h>
#include <AbstractPersona.h>

#include <Central.h>

#include "HelpPatchParser.h"

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
         virtual void componentSelected(PatchParser::Marker marker, QVariant data);
      };

   public:
      Persona(MainWidget* mainWidget);

   public:
      const QString& getCurrentKey() const;
      PatchParser parser() const;
      PatchParser& parserRef();
      void savePatchStructures();
      void buildPatchStructure(QString patchPath, const QString& key);

   private:
      using ParserMap = QMap<QString, PatchParser>;

   private slots:
      void slotReload();
      void slotSave();

   private:
      SelectModel* selectModel;
      ComponentsModel* componentsModel;
      QString currentKey;
      ParserMap parserMap;
   };
} // namespace Help

#endif // NOT HelpPersonaH
