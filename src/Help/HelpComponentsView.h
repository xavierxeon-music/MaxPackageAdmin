#ifndef HelpComponentsViewH
#define HelpComponentsViewH

#include <AbstractItemTreeView.h>

namespace Help
{
   class ComponentsModel;

   class ComponentsView : public Abstract::ItemTreeView
   {
      Q_OBJECT
   public:
      ComponentsView(QWidget* parent, ComponentsModel* model);
   };
} // namespace Help

#endif // NOT HelpComponentsViewH
