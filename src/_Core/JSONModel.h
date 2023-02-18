#ifndef JSONModelH
#define JSONModelH

#include <QStandardItemModel>

namespace JSON
{
   class Model : public QStandardItemModel
   {
      Q_OBJECT
   public:
      Model(QObject* parent);

   public:
      void readFile(const QString& filePath);

   private:
      void iterateObject(const QJsonObject& object, QStandardItem* parent);
      void iterateArray(const QJsonArray& array, QStandardItem* parent);
      void addToModel(const QString& key, const QJsonValue& value, QStandardItem* parent);
   };
} // namespace JSON

#endif // NOT JSONModelH
