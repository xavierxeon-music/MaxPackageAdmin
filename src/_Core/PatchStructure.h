#ifndef PatchStructureH
#define PatchStructureH

#include <QString>
#include <QStringList>

class PatchStructure
{
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

public:
   QString author;
   Digest patchDigest;
   MetaTagList metaTagList;
   Port::List inletList;
   Port::List outletList;
   Argument::List argumentList;
   Attribute::List attributeList;
   Message::List messageList;
   SeeAlsoList seeAlsoList;
};

#endif // NOT PatchStructureH
