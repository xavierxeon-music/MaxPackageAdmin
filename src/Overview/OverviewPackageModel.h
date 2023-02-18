#ifndef OverviewPackageModelH
#define OverviewPackageModelH

#include <Central.h>
#include <QStandardItemModel>

namespace Overview
{
   class PackageModel : public QStandardItemModel, private Central::FunctionHub
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

   private:
      void setPackagePath(QString packageDir) override;
   };
} // namespace Overview

#endif // NOT OverviewPackageModelH
