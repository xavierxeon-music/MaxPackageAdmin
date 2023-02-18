#ifndef HelpFileModelH
#define HelpFileModelH

#include "HelpPersona.h"
#include <QStandardItemModel>

namespace Help
{
   class FileModel : public QStandardItemModel,
                     private Persona::FunctionHub
   {
      Q_OBJECT

   public:
      FileModel(QObject* parent);

   private:
      void patchSelected(QString patchPath) override;
      void createEmptyHelpFile(const QString& fileName, const QString &key) const;
   };
} // namespace Help

#endif // NOT HelpFileModelH
