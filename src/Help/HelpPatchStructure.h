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
      friend class Persona;

   private:
      QDomElement createSubElement(QDomElement parent, const QString& name, const QString& text = QString(), const TagMap& tagMap = TagMap());
      void addDigest(const QDomElement& parentElement, const Digest& digest);

      void readXML();
      void readDigest(const QDomElement& parentElement, Digest& digest) const;
      QString readText(const QDomElement& element) const;
      QDomElement findFirstDirectChildElementWithAttributes(const QDomElement& element, const QString& tag, const TagMap& tagMap) const;
      QList<QDomElement> compileAllDirectChildElements(const QDomElement& element, const QString& tag, const TagMap& tagMap = TagMap()) const;

      void addJSON();
      Outlet& findOrCreateOutlet(const int id);

   private:
      QString patchName;
      QString patchPath;
      QString helpPath;
   };
} // namespace Help

#endif // NOT HelpPatchStructureH
