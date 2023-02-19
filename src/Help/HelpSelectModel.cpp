#include "HelpSelectModel.h"

#include <QDir>

Help::SelectModel::SelectModel(QObject* parent)
   : QStandardItemModel(parent)
   , Central::FunctionHub()
{
}

void Help::SelectModel::setPackagePath(QString packageDir)
{
   clear();
   setHorizontalHeaderLabels({"Patch"});

   QDir().mkpath(packageDir + "/patchers");
   QDir().mkpath(packageDir + "/docs");

   InfoMap infoMap;
   recursiveSearch(packageDir + "/patchers", infoMap);

   QMap<QString, QStandardItem*> parentMap;
   parentMap[packageDir + "/patchers"] = invisibleRootItem();

   for (InfoMap::ConstIterator it = infoMap.constBegin(); it != infoMap.constEnd(); it++)
   {
      const QString patchName = it.key();

      QStandardItem* patchItem = new QStandardItem(patchName);
      patchItem->setEditable(false);

      const QString patchPath = it.value().absoluteFilePath();
      patchItem->setData(patchPath, RolePatchPath);

      const QString patchDir = it.value().absolutePath();
      if (!parentMap.contains(patchDir))
      {
         const QString folderName = QString(patchDir).replace(packageDir + "/patchers/", "");

         QStandardItem* item = new QStandardItem(folderName);
         item->setEditable(false);
         invisibleRootItem()->appendRow(item);

         parentMap[patchDir] = item;
      }

      parentMap[patchDir]->appendRow(patchItem);
   }
}

void Help::SelectModel::recursiveSearch(const QString& path, InfoMap& infoMap)
{
   const QDir::Filters filters = QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Files | QDir::Dirs;
   for (QFileInfo fileInfo : QDir(path).entryInfoList(filters))
   {
      if (fileInfo.isDir())
      {
         recursiveSearch(fileInfo.absoluteFilePath(), infoMap);
         continue;
      }

      if (!fileInfo.fileName().endsWith(".maxpat"))
         continue;

      const QString key = fileInfo.fileName().replace(".maxpat", "");

      infoMap[key] = fileInfo;
   }
}
