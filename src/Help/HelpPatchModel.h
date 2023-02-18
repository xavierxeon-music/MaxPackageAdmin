#ifndef HelpPatchModelH
#define HelpPatchModelH

#include "HelpPersona.h"
#include <QStandardItemModel>

namespace Help
{
   class PatchModel : public QStandardItemModel,
                      private Persona::FunctionHub
   {
      Q_OBJECT

   public:
      PatchModel(QObject* parent);

   private:
      void patchSelected(QString patchPath, QString helpPath) override;
   };
} // namespace Help

#endif // NOT HelpPatchModelH
