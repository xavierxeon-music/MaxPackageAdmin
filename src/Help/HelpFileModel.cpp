#include "HelpFileModel.h"

#include <QDomDocument>
#include <QFileInfo>

#include <Central.h>

Help::FileModel::FileModel(QObject* parent)
   : QStandardItemModel(parent)
{
}

void Help::FileModel::patchSelected(QString patchPath)
{
   const QFileInfo patchInfo(patchPath);
   const QString key = patchInfo.fileName().replace(".maxpat", "");
   const QString packagePath = Central::getPackagePath();

   const QString helpFilePath = packagePath + "/docs/" + key + ".maxref.xml";
   //if (!QFile(helpFilePath).exists())
   createEmptyHelpFile(helpFilePath, key);

   clear();
}

void Help::FileModel::createEmptyHelpFile(const QString& fileName, const QString& key) const
{
   QDomDocument doc;

   QDomElement rootElement = doc.createElement("c74object");
   doc.appendChild(rootElement);

   rootElement.setAttribute("name", key);

   using TagMap = QMap<QString, QString>;

   auto createSubElement = [&](QDomElement parent, const QString& name, const QString& text = QString(), const TagMap& tagMap = TagMap())
   {
      QDomElement element = doc.createElement(name);
      parent.appendChild(element);

      if (!text.isEmpty())
      {
         QDomText textNode = doc.createTextNode("Hello World");
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

   QFile file(fileName);
   if (!file.open(QIODevice::WriteOnly))
      return;

   QByteArray content;
   content += "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n";
   content += "<?xml-stylesheet href=\"./ c74ref.xsl\" type=\"text/xsl\"?>\n";
   content += doc.toByteArray(4);

   file.write(content);
   file.close();
}
