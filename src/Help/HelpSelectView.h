#ifndef HelpSelectViewH
#define HelpSelectViewH

#include <QTreeView>

namespace Help
{
   class SelectModel;

   class SelectView : public QTreeView
   {
      Q_OBJECT
   public:
      SelectView(QWidget* parent, SelectModel* model);

   public:
      SelectModel* model;
   };
} // namespace Help

#endif // NOT HelpSelectViewH
