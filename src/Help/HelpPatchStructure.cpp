#include "HelpPatchStructure.h"

#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonValue>

#include <Central.h>
#include <JSONModel.h>

Help::PatchStructure::PatchStructure()
   : ::PatchStructure()
   , patchName()
   , patchPath()
   , helpPath()
{
}

Help::PatchStructure::PatchStructure(const QString& patchPath)
   : ::PatchStructure()
   , patchName()
   , patchPath(patchPath)
   , helpPath()
{
   const QFileInfo patchInfo(patchPath);
   patchName = patchInfo.fileName().replace(".maxpat", "");
   const QString packagePath = Central::getPackagePath();

   helpPath = packagePath + "/docs/" + patchName + ".maxref.xml";

   readXML();
   addJSON();

   if (patchDigest.text.isEmpty())
      patchDigest.text = "Hello World";

   if (!QFile::exists(helpPath))
      writeXML();
}

void Help::PatchStructure::writeXML()
{
   QDomDocument doc;

   QDomElement rootElement = doc.createElement("c74object");
   doc.appendChild(rootElement);

   rootElement.setAttribute("name", patchName);

   auto addDigest = [&](QDomElement parentElement, const Digest& digest)
   {
      createSubElement(parentElement, "digest", digest.text);
      if (!digest.description.isEmpty())
         createSubElement(parentElement, "description", digest.description);
   };

   addDigest(rootElement, patchDigest);

   QDomElement metaDataElement = createSubElement(rootElement, "metadatalist");
   createSubElement(metaDataElement, "metadata", Central::getAuthor(), {{"name", "author"}});
   createSubElement(metaDataElement, "metadata", Central::getPackageName(), {{"name", "tag"}});

   QDomElement outletListElement = createSubElement(rootElement, "misc");
   outletListElement.setAttribute("name", "Outputs");
   for (Port::Map::ConstIterator it = outletMap.constBegin(); it != outletMap.constEnd(); it++)
   {
      QDomElement outletElement = createSubElement(outletListElement, "entry");
      outletElement.setAttribute("name", it.value().name);
      outletElement.setAttribute("id", QString::number(it.key()));

      createSubElement(outletElement, it.value().description);
   }

   QDomElement objArgListElement = createSubElement(rootElement, "objarglist");
   for (const Argument& argument : argumentList)
   {
      QDomElement arguemntElement = createSubElement(objArgListElement, "objarg");
      arguemntElement.setAttribute("name", argument.name);
      arguemntElement.setAttribute("optional", argument.optional ? "1" : "0");
      arguemntElement.setAttribute("type", typeName(argument.type));

      addDigest(arguemntElement, argument.digest);
   }

   QDomElement attributeListElement = createSubElement(rootElement, "attributelist");
   for (const Attribute& attribute : attributeList)
   {
      QDomElement attributeElement = createSubElement(attributeListElement, "attribute");
      attributeElement.setAttribute("name", attribute.name);
      attributeElement.setAttribute("get", attribute.get ? "1" : "0");
      attributeElement.setAttribute("set", attribute.set ? "1" : "0");
      attributeElement.setAttribute("type", typeName(attribute.type));
      attributeElement.setAttribute("size", QString::number(attribute.size));

      addDigest(attributeElement, attribute.digest);
   }

   QDomElement messageListElement = createSubElement(rootElement, "methodlist");
   for (Message::Map::ConstIterator it = messageMap.constBegin(); it != messageMap.constEnd(); it++)
   {
      const Message& message = it.value();

      QDomElement messageElement = createSubElement(messageListElement, "method");
      messageElement.setAttribute("name", it.key());

      if (!message.arguments.empty())
      {
         QDomElement argListElement = createSubElement(messageElement, "arglist");
         for (const Argument& argument : message.arguments)
         {
            QDomElement arguemntElement = createSubElement(argListElement, "arg");
            arguemntElement.setAttribute("name", argument.name);
            arguemntElement.setAttribute("optional", argument.optional ? "1" : "0");
            arguemntElement.setAttribute("type", typeName(argument.type));
         }
      }

      addDigest(messageElement, message.digest);

      for (QMap<int, QString>::ConstIterator it2 = message.inletDescriptions.constBegin(); it2 != message.inletDescriptions.constEnd(); it2++)
      {
         QDomElement inletDescriptonElement = createSubElement(messageElement, "inlet", it2.value());
         inletDescriptonElement.setAttribute("id", QString::number(it2.key()));
      }
   }

   QDomElement seeAlsoListElement = createSubElement(rootElement, "seealsolist");
   for (const QString& seeAlso : seeAlsoList)
   {
      createSubElement(seeAlsoListElement, "seealso", QString(), {{"name", seeAlso}});
   }

   QFile file(helpPath);
   if (!file.open(QIODevice::WriteOnly))
      return;

   QByteArray content;
   content += "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n";
   content += "<?xml-stylesheet href=\"./_c74_ref.xsl\" type=\"text/xsl\"?>\n";
   content += doc.toByteArray(4);

   file.write(content);
   file.close();
}

void Help::PatchStructure::readXML()
{
}

void Help::PatchStructure::addJSON()
{
   QJsonObject object = JSON::fromFile(patchPath);
   if (object.empty())
      return;

   const QJsonObject patcherObject = object["patcher"].toObject();
   const QJsonArray boxArray = patcherObject["boxes"].toArray();
   const QJsonArray lineArray = patcherObject["lines"].toArray();

   struct Inlet
   {
      int index;
      QStringList connectedIdList;
   };

   using InletConnectionMap = QMap<QString, Inlet>;
   InletConnectionMap inletConnectionMap;

   // parse inlets, outlets and patcherargs
   for (int index = 0; index < boxArray.size(); index++)
   {
      QJsonObject boxObject = boxArray.at(index).toObject();
      boxObject = boxObject["box"].toObject();

      if (!boxObject.contains("maxclass"))
         continue;

      const QString className = boxObject["maxclass"].toString();
      if ("inlet" == className)
      {
         const int index = boxObject["index"].toInt();
         Port& inlet = findOrCreatePort(inletMap, index);

         const QString comment = boxObject["comment"].toString();
         if (inlet.name.isEmpty())
            inlet.name = comment;

         const QString id = boxObject["id"].toString();
         inletConnectionMap[id] = {index, QStringList()};
      }
      else if ("outlet" == className)
      {
         const int index = boxObject["index"].toInt();
         Port& outlet = findOrCreatePort(outletMap, index);

         const QString comment = boxObject["comment"].toString();
         if (outlet.name.isEmpty())
            outlet.name = comment;
      }
      else if ("newobj" == className)
      {
         const QString text = boxObject["text"].toString();
         if (!text.startsWith("patcherargs"))
            continue;

         const QStringList contentList = text.split(" ", Qt::SkipEmptyParts);
         enum class State
         {
            Argument,
            AttributeName,
            AttributeArg
         };

         State state = State::Argument;

         for (int i = 1; i < contentList.size(); i++)
         {
            const QString& arg = contentList.at(i);

            // maybe advance state
            if (arg.startsWith("@"))
               state = State::AttributeName;
            else if (State::AttributeName == state)
               state = State::AttributeArg;

            if (State::Argument == state)
            {
               Argument argument;
               argument.digest.text = arg;
               argument.optional = true;

               argumentList.append(argument);
            }
            else if (State::AttributeName == state)
            {
               Attribute attribute;
               attribute.name = arg.mid(1);

               attributeList.append(attribute);
            }
         }
      }
   }

   // find objects connected to inlets
   for (int index = 0; index < lineArray.size(); index++)
   {
      QJsonObject lineObject = lineArray.at(index).toObject();
      lineObject = lineObject["patchline"].toObject();

      const QJsonArray destArray = lineObject["destination"].toArray();
      const QString destId = destArray.at(0).toString();

      const QJsonArray sourceArray = lineObject["source"].toArray();
      const QString sourceId = sourceArray.at(0).toString();

      if (inletConnectionMap.contains(destId))
         inletConnectionMap[destId].connectedIdList.append(sourceId);
      else if (inletConnectionMap.contains(sourceId))
         inletConnectionMap[sourceId].connectedIdList.append(destId);
   }

   // parse routes connected to inlets for  messages
   for (int index = 0; index < boxArray.size(); index++)
   {
      QJsonObject boxObject = boxArray.at(index).toObject();
      boxObject = boxObject["box"].toObject();

      if (!boxObject.contains("maxclass"))
         continue;

      const QString className = boxObject["maxclass"].toString();
      if ("newobj" == className)
      {
         const QString text = boxObject["text"].toString();
         if (!text.startsWith("route"))
            continue;

         // check if connected to inlet
         int connectedIndex = [&]() -> int
         {
            const QString routeId = boxObject["id"].toString();
            for (InletConnectionMap::ConstIterator it = inletConnectionMap.constBegin(); it != inletConnectionMap.constEnd(); it++)
            {
               for (const QString& id : it.value().connectedIdList)
               {
                  if (id == routeId)
                     return it.value().index;
               }
            }
            return -1;
         }();

         if (-1 == connectedIndex)
            continue;

         const QStringList contentList = text.split(" ", Qt::SkipEmptyParts);
         for (int i = 1; i < contentList.size(); i++)
         {
            const QString& messageText = contentList.at(i);

            Message& message = messageMap[messageText];
            if (!message.inletDescriptions.contains(connectedIndex))
               message.inletDescriptions[connectedIndex] = QString();
         }
      }
   }
}

QDomElement Help::PatchStructure::createSubElement(QDomElement parent, const QString& name, const QString& text, const TagMap& tagMap)
{
   QDomElement element = parent.ownerDocument().createElement(name);
   parent.appendChild(element);

   if (!text.isEmpty())
   {
      QDomText textNode = parent.ownerDocument().createTextNode(text);
      element.appendChild(textNode);
   }

   for (TagMap::ConstIterator it = tagMap.constBegin(); it != tagMap.constEnd(); it++)
   {
      element.setAttribute(it.key(), it.value());
   }

   return element;
}

PatchStructure::Port& Help::PatchStructure::findOrCreatePort(Port::Map& portMap, const int id)
{
   if (!portMap.contains(id))
      portMap[id] = Port{};

   return portMap[id];
}
