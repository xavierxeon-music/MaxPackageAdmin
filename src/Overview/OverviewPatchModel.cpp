#include "OverviewPatchModel.h"

#include <limits.h>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include "Message.h"

Overview::PatchModel::PatchModel(QObject* parent)
   : QStandardItemModel(parent)
   , FunctionHub()
{
}

void Overview::PatchModel::patchSelected(QString patchPath)
{
   qDebug() << __FUNCTION__ << patchPath;

   clear();

   setHorizontalHeaderLabels({"Name", "Type", "Value"});

   if (patchPath.isEmpty())
      return;

   QFile file(patchPath);
   if (!file.open(QIODevice::ReadOnly))
      return Message::error(QString("unalbe to read file %1").arg(patchPath));

   const QByteArray content = file.readAll();
   file.close();

   QJsonParseError parserStatus;
   QJsonDocument doc = QJsonDocument::fromJson(content, &parserStatus);
   if (parserStatus.error != QJsonParseError::NoError)
      return Message::error(parserStatus.errorString());

   QJsonObject object = doc.object();
   iterateObject(object, invisibleRootItem());

   emit signalUpdated();
}

void Overview::PatchModel::iterateObject(const QJsonObject& object, QStandardItem* parent)
{
   for (const QString& key : object.keys())
   {
      const QJsonValue value = object[key];
      addToModel(key, value, parent);
   }
}

void Overview::PatchModel::iterateArray(const QJsonArray& array, QStandardItem* parent)
{
   const int itemCount = array.count();
   for (int index = 0; index < itemCount; index++)
   {
      const QString key = QString::number(index);
      const QJsonValue value = array.at(index);
      addToModel(key, value, parent);
   }
}

void Overview::PatchModel::addToModel(const QString& key, const QJsonValue& value, QStandardItem* parent)
{
   QStandardItem* nameItem = new QStandardItem();
   nameItem->setEditable(false);
   nameItem->setText(key);

   QStandardItem* typeItem = new QStandardItem();
   typeItem->setEditable(false);

   QStandardItem* valueItem = new QStandardItem();
   valueItem->setEditable(false);

   switch (value.type())
   {
      case QJsonValue::Object:
      {
         typeItem->setText("object");

         const QJsonObject childObject = value.toObject();
         iterateObject(childObject, nameItem);

         valueItem->setText(QString("%1 keys").arg(childObject.keys().count()));
         break;
      }
      case QJsonValue::Array:
      {
         typeItem->setText("array");

         const QJsonArray childArray = value.toArray();
         iterateArray(childArray, nameItem);

         valueItem->setText(QString("%1 entries").arg(childArray.count()));
         break;
      }
      case QJsonValue::Bool:
      {
         typeItem->setText("boolean");

         const bool boolean = value.toBool();
         valueItem->setText(boolean ? "true" : "fasle");
         break;
      }
      case QJsonValue::Double:
      {
         static const qint64 defaultNumber = std::numeric_limits<qint64>::max();

         const qint64 intNumber = value.toInteger(defaultNumber);
         if (defaultNumber != intNumber)
         {
            typeItem->setText("integer");
            valueItem->setText(QString::number(intNumber));
         }
         else
         {
            typeItem->setText("float");
            const double floatNumber = value.toDouble();
            valueItem->setText(QString::number(floatNumber));
         }

         break;
      }
      case QJsonValue::String:
      {
         typeItem->setText("string");

         const QString& string = value.toString();
         valueItem->setText(string);
         break;
      }

      default:
      {
         typeItem->setText("value");
         break;
      }
   }

   parent->appendRow({nameItem, typeItem, valueItem});
}
