#ifndef PatchStructureH
#define PatchStructureH

#include <QMap>
#include <QString>
#include <QStringList>

class PatchStructure
{
public:
   enum Type
   {
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

   struct Port
   {
      QString name;
      QString description;

      using Map = QMap<int, Port>; // inlet number vs port
   };

   // things in patcherargs without @
   // message argumetns
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
      Argument::List arguments;
      Digest digest;

      QMap<int, QString> inletDescriptions; // for example name = "int" on inlet 1 or 2 or 3...

      using Map = QMap<QString, Message>; // name vs message
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
   Port::Map inletMap;
   Port::Map outletMap;
   Argument::List argumentList;
   Attribute::List attributeList;
   Message::Map messageMap;
   SeeAlsoList seeAlsoList;

public:
   QString typeName(const Type& type);
};

#endif // NOT PatchStructureH
