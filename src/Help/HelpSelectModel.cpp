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

   for (InfoMap::ConstIterator it = infoMap.constBegin(); it != infoMap.constEnd(); it++)
   {
      const QString patchName = it.key();

      QStandardItem* patchItem = new QStandardItem(patchName);
      patchItem->setEditable(false);
      patchItem->setData(it.value(), RolePatchPath);

      invisibleRootItem()->appendRow(patchItem);
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

      infoMap[key] = fileInfo.absoluteFilePath();
   }
}
