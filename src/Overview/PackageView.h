#ifndef PackageViewH
#define PackageViewH

#include <QTreeView>

namespace Package
{
   class Model;

   class View : public QTreeView
   {
      Q_OBJECT
   public:
      View(QWidget* parent, Model* model);

   signals:
      void signalPatchSelected(const QString& patchPath);

   public slots:
      void slotClicked(const QModelIndex& index);

   private:
      Model* model;
   };
} // namespace Package

#endif // NOT PackageViewH
