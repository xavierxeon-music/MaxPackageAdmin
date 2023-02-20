#ifndef PatchStructureH
#define PatchStructureH

#include <QMap>
#include <QString>
#include <QStringList>

class PatchStructure
{
public:
   enum class Type
   {
      Unkown,
      Symbol,
      Float,
      Integer,
      Bang
   };

   struct Digest
   {
      QString text;
      QString description;
   };

   using MetaTagList = QStringList;

   struct Output
   {
      QString name;
      QString description;

      using Map = QMap<int, Output>; // outlet number vs port
   };

   // things in patcherargs without @
   // message argumetns
   struct Argument
   {
      QString name;
      bool optional;
      Type type = Type::Symbol;
      Digest digest;

      using List = QList<Argument>;
   };

   struct Message
   {
      Argument::List arguments;
      Digest digest;

      using Map = QMap<QString, Message>; // name vs message
   };

   // things in patcherargs with @
   struct Attribute
   {
      bool get;
      bool set;
      Type type = Type::Symbol;
      int size = 1;
      Digest digest;

      using Map = QMap<QString, Attribute>; // name vs message
   };

   using SeeAlsoList = QStringList;

public:
   Digest patchDigest;
   MetaTagList metaTagList;
   Output::Map outputMap;
   Argument::List argumentList;
   Attribute::Map attributeMap;
   Message::Map messageMap;
   SeeAlsoList seeAlsoList;

public:
   QString typeName(const Type& type);
   Type toType(const QString& name);
};

#endif // NOT PatchStructureH
