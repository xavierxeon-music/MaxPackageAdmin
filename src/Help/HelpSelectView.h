#ifndef HelpSelectViewH
#define HelpSelectViewH

#include "HelpPersona.h"
#include <AbstractItemTreeView.h>

namespace Help
{
   class SelectModel;

   class SelectView : public Abstract::ItemTreeView,
                      private Persona::FunctionHub
   {
      Q_OBJECT
   public:
      SelectView(QWidget* parent, SelectModel* model);

   public:
      void clicked(QStandardItem* item) override;
   };
} // namespace Help

#endif // NOT HelpSelectViewH
