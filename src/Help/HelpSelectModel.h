#ifndef HelpSelectModelH
#define HelpSelectModelH

#include <Central.h>
#include <QStandardItemModel>

#include "HelpPersona.h"
#include <QFileInfo>

namespace Help
{
   class SelectModel : public QStandardItemModel,
                       private Central::FunctionHub
   {
      Q_OBJECT

   public:
      enum Role
      {
         RolePatchPath = Qt::UserRole + 1,
         RoleHelpPath
      };

   public:
      SelectModel(QObject* parent);

   private:
      using InfoVar = QString Info::*;
      using InfoMap = QMap<QString, Info>;

   private:
      void setPackagePath(QString packageDir) override;
      void recursiveSearch(const QString& path, const QString& suffix, InfoVar infoVar, InfoMap& infoMap);
   };
} // namespace Help

#endif // NOT HelpSelectModelH
