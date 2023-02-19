#ifndef HelpComponentsModelH
#define HelpComponentsModelH

#include "HelpPersona.h"
#include <QStandardItemModel>

namespace Help
{
   class ComponentsModel : public QStandardItemModel,
                           private Persona::FunctionHub
   {
      Q_OBJECT

   public:
      ComponentsModel(QObject* parent);

   private:
      void patchSelected(QString patchPath) override;
   };
} // namespace Help

#endif // NOT HelpComponentsModelH
