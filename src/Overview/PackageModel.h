#ifndef PackageModelH
#define PackageModelH

#include <QStandardItemModel>

namespace Package
{
   class Model : public QStandardItemModel
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
      Model(QObject* parent);

   public:
      void setPath(const QString& packageDir);
   };
} // namespace Package

#endif // NOT PackageModelH
