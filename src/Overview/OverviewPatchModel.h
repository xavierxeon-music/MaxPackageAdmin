#ifndef OverviewPatchModelH
#define OverviewPatchModelH

#include "OverviewPersona.h"
#include <QStandardItemModel>

namespace Overview
{
   class PatchModel : public QStandardItemModel, private FunctionHub
   {
      Q_OBJECT
   public:
      PatchModel(QObject* parent);

   signals:
      void signalUpdated();

   private:
      void patchSelected(QString patchPath) override;
      void iterateObject(const QJsonObject& object, QStandardItem* parent);
      void iterateArray(const QJsonArray& array, QStandardItem* parent);
      void addToModel(const QString& key, const QJsonValue& value, QStandardItem* parent);
   };
} // namespace Overview

#endif // NOT OverviewPatchModelH
