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
      ComponentsModel(Persona* persona);

   private:
      void patchSelected(QString patchPath) override;

   private:
      Persona* persona;
   };
} // namespace Help

#endif // NOT HelpComponentsModelH
