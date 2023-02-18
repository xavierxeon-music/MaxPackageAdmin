#ifndef PatchRawViewH
#define PatchRawViewH

#include <QTreeView>

namespace Patch
{
   class RawModel;

   class RawView : public QTreeView
   {
      Q_OBJECT
   public:
      RawView(QWidget* parent, RawModel* model);

   private slots:
      void slotResizeAllColumns();

   private:
      RawModel* model;
   };
} // namespace Patch

#endif // NOT PatchRawViewH
