#ifndef HelpPatchStructureH
#define HelpPatchStructureH

#include <PatchStructure.h>

#include <QDomElement>
#include <QMap>
#include <QObject>

namespace Help
{
   class PatchStructure : public ::PatchStructure
   {
      Q_GADGET
   public:
      enum Role
      {
         RoleMarker = Qt::UserRole + 1,
         RoleData = Qt::UserRole + 2
      };

      enum class Marker
      {
         Patch,
         Argument,
         Attribute,
         Mesasge,
         Outlet
      };
      Q_ENUM(Marker)

   public:
      PatchStructure();
      PatchStructure(const QString& patchPath);

   public:
      void writeXML();

   private:
      using TagMap = QMap<QString, QString>;
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
