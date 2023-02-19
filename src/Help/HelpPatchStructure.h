#ifndef HelpPatchStructureH
#define HelpPatchStructureH

#include <PatchStructure.h>

#include <QDomElement>
#include <QMap>

namespace Help
{
   class PatchStructure : public ::PatchStructure
   {
   public:
      PatchStructure();
      PatchStructure(const QString& patchPath);

   public:
      void writeXML();

   private:
      using TagMap = QMap<QString, QString>;

   private:
      void readXML();
      void addJSON();

      QDomElement createSubElement(QDomElement parent, const QString& name, const QString& text = QString(), const TagMap& tagMap = TagMap());
      Port& findOrCreatePort(Port::List& portList, const int id);

   private:
      QString patchName;
      QString patchPath;
      QString helpPath;
   };
} // namespace Help

#endif // NOT HelpPatchStructureH
