#ifndef HelpSelectViewH
#define HelpSelectViewH

#include "HelpPersona.h"
#include <AbstractItemTreeView.h>

namespace Help
{
   class SelectModel;
   class Persona;

   class SelectView : public Abstract::ItemTreeView,
                      private Persona::FunctionHub
   {
      Q_OBJECT
   public:
      SelectView(Persona* persona, SelectModel* model);

   private:
      void clicked(QStandardItem* item) override;
      void doubleClicked(QStandardItem* item) override;

   private:
      Persona* persona;
   };
} // namespace Help

#endif // NOT HelpSelectViewH
