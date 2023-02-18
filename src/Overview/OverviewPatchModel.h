#ifndef OverviewPatchModelH
#define OverviewPatchModelH

#include <QStandardItemModel>

namespace Overview
{
   class PatchModel : public QStandardItemModel
   {
      Q_OBJECT
   public:
      PatchModel(QObject* parent);

   signals:
      void signalUpdated();

   public slots:
      void slotSetPatch(const QString& patchPath);

   private:
      void iterateObject(const QJsonObject& object, QStandardItem* parent);
      void iterateArray(const QJsonArray& array, QStandardItem* parent);
      void addToModel(const QString& key, const QJsonValue& value, QStandardItem* parent);
   };
} // namespace Overview

#endif // NOT OverviewPatchModelH
