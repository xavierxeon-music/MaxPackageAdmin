#include "HelpPatchModel.h"

#include <QJsonArray>
#include <QJsonValue>

#include <JSONModel.h>

Help::PatchModel::PatchModel(QObject* parent)
   : QStandardItemModel(parent)
   , Persona::FunctionHub()
{
}

void Help::PatchModel::patchSelected(QString patchPath, QString helpPath)
{
   Q_UNUSED(helpPath)
   clear();

   setHorizontalHeaderLabels({"Type / Name", "Comment"});

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
         const QString inletText = QString("Inlet %1").arg(boxObject["index"].toInt());
         QStandardItem* inletItem = new QStandardItem(inletText);
         inletItem->setEditable(false);

         const QString comment = boxObject["comment"].toString();
         QStandardItem* textItem = new QStandardItem(comment);
         textItem->setEditable(false);

         invisibleRootItem()->appendRow({inletItem, textItem});
      }
      else if ("outlet" == className)
      {
         const QString outletText = QString("Outlet %1").arg(boxObject["index"].toInt());
         QStandardItem* outletItem = new QStandardItem(outletText);
         outletItem->setEditable(false);

         const QString comment = boxObject["comment"].toString();
         QStandardItem* textItem = new QStandardItem(comment);

         invisibleRootItem()->appendRow({outletItem, textItem});
      }
      else if ("newobj" == className)
      {
         const QString text = boxObject["text"].toString();
         if (text.startsWith("patcherargs"))
         {
            QStandardItem* patcherArgsItem = new QStandardItem("Arguments");

            const QString comment = text.mid(12);
            QStandardItem* textItem = new QStandardItem(comment);

            invisibleRootItem()->appendRow({patcherArgsItem, textItem});
         }
         else if (text.startsWith("route"))
         {
            QStandardItem* routeItem = new QStandardItem("Route");

            const QString comment = text.mid(6);
            QStandardItem* textItem = new QStandardItem(comment);

            invisibleRootItem()->appendRow({routeItem, textItem});
         }
      }
      else
      {
      }
   }

   const QJsonArray lineArray = patcherObject["lines"].toArray();
   for (int index = 0; index < lineArray.size(); index++)
   {
   }
}
