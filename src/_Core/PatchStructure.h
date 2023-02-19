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
      Integer
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
      Digest digest;

      using List = QList<Port>;
   };

   // things in patcherargs without @
   struct Argument
   {
      QString name;
      bool optional;
      Type type = Symbol;
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
      Type type = Symbol;
      int size = 1;
      Digest digest;

      using List = QList<Attribute>;
   };

   using SeeAlsoList = QStringList;

public:
   Digest patchDigest;
   MetaTagList metaTagList;
   Port::List inletList;
   Port::List outletList;
   Argument::List argumentList;
   Attribute::List attributeList;
   Message::List messageList;
   SeeAlsoList seeAlsoList;

public:
   QString typeName(const Type& type);
};

#endif // NOT PatchStructureH
