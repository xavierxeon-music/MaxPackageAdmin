#include "HelpPatchStructure.h"

#include <QDomDocument>
#include <QFile>
#include <QFileInfo>

#include <Central.h>

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
   if (!QFile::exists(helpPath))
      writeXML();
}

void Help::PatchStructure::writeXML()
{
   QDomDocument doc;

   QDomElement rootElement = doc.createElement("c74object");
   doc.appendChild(rootElement);

   rootElement.setAttribute("name", patchName);

   using TagMap = QMap<QString, QString>;

   auto createSubElement = [&](QDomElement parent, const QString& name, const QString& text = QString(), const TagMap& tagMap = TagMap())
   {
      QDomElement element = parent.ownerDocument().createElement(name);
      parent.appendChild(element);

      if (!text.isEmpty())
      {
         QDomText textNode = parent.ownerDocument().createTextNode("Hello World");
         element.appendChild(textNode);
      }

      for (TagMap::ConstIterator it = tagMap.constBegin(); it != tagMap.constEnd(); it++)
      {
         element.setAttribute(it.key(), it.value());
      }

      return element;
   };

   createSubElement(rootElement, "digest", "text");
   createSubElement(rootElement, "description", "text");

   QDomElement metaDataElement = createSubElement(rootElement, "metadatalist");
   createSubElement(metaDataElement, "metadata", "YorName", {{"name", "author"}});
   createSubElement(metaDataElement, "metadata", "WaMaxPackage", {{"name", "tag"}});

   createSubElement(rootElement, "inletlist");
   createSubElement(rootElement, "outletlist");
   createSubElement(rootElement, "objarglist");
   createSubElement(rootElement, "methodlist");
   createSubElement(rootElement, "attributelist");
   createSubElement(rootElement, "seealsolist");

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
}
