#ifndef PatchRawModelH
#define PatchRawModelH

#include <QStandardItemModel>

namespace Patch
{
   class RawModel : public QStandardItemModel
   {
      Q_OBJECT
   public:
      RawModel(QObject* parent);

   signals:
      void signalUpdated();

   public slots:
      void slotSetPatch(const QString& patchPath);

   private:
      void iterateModel(const QJsonObject& object, QStandardItem* parent);
      void iterateModel(const QJsonArray& array, QStandardItem* parent);
      void addToModel(const QString& key, const QJsonValue& value, QStandardItem* parent);
   };
} // namespace Patch

#endif // NOT PatchModelH
