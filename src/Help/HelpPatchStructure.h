#ifndef HelpPatchStructureH
#define HelpPatchStructureH

#include <QString>
#include <QStringList>

namespace Help
{
   class PatchStructure
   {
   public:
      PatchStructure();
      PatchStructure(const QString& patchPath, const QString& helpPath);

   public:
      enum Type
      {
         Symbol,
         Float,
         Int
      };

      struct Digest
      {
         QString text;
         QString description;
      };

      using MetaTagList = QStringList;

      struct Port
      {
         int id;
         Type type;
         Digest digest;

         using List = QList<Port>;
      };

      // things in patcherargs without @
      struct Argument
      {
         QString name;
         bool optional;
         Type type;
         Digest digest;

         using List = QList<Argument>;
      };

      struct Message
      {
         QString name;
         Argument::List arguments;
         Digest digest;

         using List = QList<Message>;
      };

      // things in patcherargs with @
      struct Attribute
      {
         QString name;
         bool get;
         bool set;
         Type type;
         int size;
         Digest digest;

         using List = QList<Attribute>;
      };

      using SeeAlsoList = QStringList;

   private:
      QString patchPath;
      QString helpPath;

      Digest patchDigest;
      MetaTagList metaTagList;
      Port::List inletList;
      Port::List outletList;
      Argument::List argumentList;
      Attribute::List attributeList;
      Message::List messageList;
   };
} // namespace Help

#endif // NOT HelpPatchStructureH
