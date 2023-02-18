#ifndef HelpFileViewH
#define HelpFileViewH

#include <QTreeView>

namespace Help
{
   class FileModel;

   class FileView : public QTreeView
   {
      Q_OBJECT
   public:
      FileView(QWidget* parent, FileModel* model);

   private:
      FileModel* model;
   };
} // namespace Help

#endif // NOT HelpFileViewH
