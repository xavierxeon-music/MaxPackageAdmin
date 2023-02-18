#include "PatchModel.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include "MessageWidget.h"

Patch::Model::Model(QObject* parent)
   : QStandardItemModel(parent)
{
}

void Patch::Model::slotSetPatch(const QString& patchPath)
{
   clear();

   setHorizontalHeaderLabels({"Name", "Value"});

   if (patchPath.isEmpty())
      return;

   QFile file(patchPath);
   if (!file.open(QIODevice::ReadOnly))
      return MessageWidget::error(QString("unalbe to read file %1").arg(patchPath));

   const QByteArray content = file.readAll();
   file.close();

   QJsonParseError parserStatus;
   QJsonDocument doc = QJsonDocument::fromJson(content, &parserStatus);
   if (parserStatus.error != QJsonParseError::NoError)
      return MessageWidget::error(parserStatus.errorString());

   std::function<void(const QJsonObject& object, QStandardItem*)> buildModel = [&](const QJsonObject& object, QStandardItem* parent)
   {
      for (const QString& key : object.keys())
      {
         QStandardItem* nameItem = new QStandardItem();
         nameItem->setText(key);

         QStandardItem* valueItem = new QStandardItem();

         const QJsonValue value = object[key];
         if (value.isObject())
         {
            const QJsonObject childObject = value.toObject();
            buildModel(childObject, nameItem);

            valueItem->setText("object");
         }
         else if (value.isArray())
         {
            valueItem->setText("array");
         }
         else
         {
            valueItem->setText("value");
         }

         parent->appendRow({nameItem, valueItem});
      }
   };

   QJsonObject object = doc.object();
   buildModel(object, invisibleRootItem());
}
