#include "OverviewPackageModel.h"

#include <QDir>

Overview::PackageModel::PackageModel(QObject* parent)
   : QStandardItemModel(parent)
   , Central::FunctionHub()
{
}

void Overview::PackageModel::setPackagePath(QString packageDir)
{
   clear();

   setHorizontalHeaderLabels({"Name"});

   const QDir::Filters filters = QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Files | QDir::Dirs;
   for (QFileInfo fileInfo : QDir(packageDir).entryInfoList(filters))
   {
      if (fileInfo.isFile() && "package-info.json" == fileInfo.fileName())
      {
         QStandardItem* infoItem = new QStandardItem("INFO");
         infoItem->setEditable(false);
         invisibleRootItem()->appendRow(infoItem);
         infoItem->setData(fileInfo.absoluteFilePath(), RoleInfo);
      }

      else if (fileInfo.isDir() && "patchers" == fileInfo.fileName())
      {
         QStandardItem* patchParentItem = new QStandardItem("patches");
         patchParentItem->setEditable(false);
         invisibleRootItem()->appendRow(patchParentItem);

         std::function<void(const QString)> recursiveFillPatches = [&](const QString dirPath)
         {
            for (QFileInfo fileInfo : QDir(dirPath).entryInfoList(filters))
            {
               if (fileInfo.isDir())
               {
                  recursiveFillPatches(fileInfo.absoluteFilePath());
                  continue;
               }
               if ("maxpat" != fileInfo.suffix())
                  continue;

               const QString name = fileInfo.fileName().replace(".maxpat", "");
               QStandardItem* patchItem = new QStandardItem(name);
               patchItem->setEditable(false);
               patchItem->setData(fileInfo.absoluteFilePath(), RolePatch);
               patchParentItem->appendRow(patchItem);
            }
         };

         recursiveFillPatches(fileInfo.absoluteFilePath());
      }
      else if (fileInfo.isDir() && "docs" == fileInfo.fileName())
      {
         QStandardItem* helpItem = new QStandardItem("help");
         invisibleRootItem()->appendRow(helpItem);

         //recursiveFill(fileInfo.absoluteFilePath(), RoleHelp, helpItem);
      }
   }
}
