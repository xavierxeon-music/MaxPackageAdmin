#ifndef HelpFileViewH
#define HelpFileViewH

#include <AbstractItemTreeView.h>

namespace Help
{
   class FileModel;

   class FileView : public Abstract::ItemTreeView
   {
      Q_OBJECT
   public:
      FileView(QWidget* parent, FileModel* model);
   };
} // namespace Help

#endif // NOT HelpFileViewH
