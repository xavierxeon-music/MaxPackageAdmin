#ifndef OverviewPackageModelH
#define OverviewPackageModelH

#include <QStandardItemModel>

namespace Overview
{
   class PackageModel : public QStandardItemModel
   {
      Q_OBJECT

   public:
      enum Role
      {
         RoleInfo = Qt::UserRole + 1,
         RolePatch = Qt::UserRole + 2,
         RoleHelp = Qt::UserRole + 3,
      };

   public:
      PackageModel(QObject* parent);

   public:
      void setPath(const QString& packageDir);
   };
} // namespace Overview

#endif // NOT OverviewPackageModelH
