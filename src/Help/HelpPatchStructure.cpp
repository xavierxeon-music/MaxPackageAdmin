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

   //if (!QFile::exists(helpPath))
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

   QDomElement inletListElement = createSubElement(rootElement, "misc");
   inletListElement.setAttribute("name", "Inputs");
   for (const Port& port : inletList)
   {
      QDomElement inletElement = createSubElement(inletListElement, "entry");
      inletElement.setAttribute("name", "Input " + QString::number(port.id));

      addDigest(inletElement, port.digest);
   }

   QDomElement outletListElement = createSubElement(rootElement, "misc");
   outletListElement.setAttribute("name", "Outputs");
   for (const Port& port : outletList)
   {
      QDomElement outletElement = createSubElement(outletListElement, "entry");
      outletElement.setAttribute("name", "Output " + QString::number(port.id));

      addDigest(outletElement, port.digest);
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
   for (const Message& message : messageList)
   {
      QDomElement messageElement = createSubElement(messageListElement, "method");
      messageElement.setAttribute("name", message.name);

      QDomElement argListElement = createSubElement(messageElement, "arglist");
      for (const Argument& argument : message.arguments)
      {
         QDomElement arguemntElement = createSubElement(argListElement, "arg");
         arguemntElement.setAttribute("name", argument.name);
         arguemntElement.setAttribute("optional", argument.optional ? "1" : "0");
         arguemntElement.setAttribute("type", typeName(argument.type));
      }

      addDigest(messageElement, message.digest);
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
   content += "<?xml-stylesheet href=\"./ c74ref.xsl\" type=\"text/xsl\"?>\n";
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
         Port& inlet = findOrCreatePort(inletList, index);

         const QString comment = boxObject["comment"].toString();
         if (inlet.digest.text.isEmpty())
            inlet.digest.text = comment;
      }
      else if ("outlet" == className)
      {
         const int index = boxObject["index"].toInt();
         Port& outlet = findOrCreatePort(outletList, index);

         const QString comment = boxObject["comment"].toString();
         if (outlet.digest.text.isEmpty())
            outlet.digest.text = comment;
      }
      else if ("newobj" == className)
      {
         const QString text = boxObject["text"].toString();
         const QStringList contentList = text.split(" ", Qt::SkipEmptyParts);
         if (text.startsWith("patcherargs"))
         {
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
         else if (text.startsWith("route"))
         {
         }
      }
      else
      {
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

PatchStructure::Port& Help::PatchStructure::findOrCreatePort(Port::List& portList, const int id)
{
   for (Port& port : portList)
   {
      if (id == port.id)
         return port;
   }

   Port port;
   port.id = id;

   const int index = portList.size();
   portList.append(port); // this makes a copy

   return portList[index]; // we can not return local port
}
