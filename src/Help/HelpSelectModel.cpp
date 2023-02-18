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

   InfoMap infoMap;
   recursiveSearch(packageDir + "/patchers", "maxpat", &Info::patchPath, infoMap);
   recursiveSearch(packageDir + "/doc", "maxref.xml", &Info::helpPath, infoMap);

   for (InfoMap::ConstIterator it = infoMap.constBegin(); it != infoMap.constEnd(); it++)
   {
      const QString patchName = it.key();

      QStandardItem* patchItem = new QStandardItem(patchName);
      patchItem->setEditable(false);

      const bool helpAvailable = !it.value().helpPath.isEmpty();
      patchItem->setCheckState(helpAvailable ? Qt::Checked : Qt::Unchecked);

      patchItem->setData(it.value().patchPath, RolePatchPath);
      patchItem->setData(it.value().helpPath, RoleHelpPath);

      invisibleRootItem()->appendRow(patchItem);
   }
}

void Help::SelectModel::recursiveSearch(const QString& path, const QString& suffix, InfoVar infoVar, InfoMap& infoMap)
{
   const QDir::Filters filters = QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Files | QDir::Dirs;
   for (QFileInfo fileInfo : QDir(path).entryInfoList(filters))
   {
      if (fileInfo.isDir())
      {
         recursiveSearch(fileInfo.absoluteFilePath(), suffix, infoVar, infoMap);
         continue;
      }

      if (!fileInfo.fileName().endsWith(suffix))
         continue;

      const QString key = fileInfo.fileName().replace("." + suffix, "");

      if (!infoMap.contains(key))
         infoMap[key] = Info{};

      Info* info = &infoMap[key];
      info->*infoVar = fileInfo.absoluteFilePath();
   }
}
