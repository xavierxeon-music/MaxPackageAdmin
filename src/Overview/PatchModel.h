#ifndef PatchModelH
#define PatchModelH

#include <QStandardItemModel>

namespace Patch
{
   class Model : public QStandardItemModel
   {
      Q_OBJECT
   public:
      Model(QObject* parent);

   public slots:
      void slotSetPatch(const QString& patchPath);
   };
} // namespace Patch

#endif // NOT PatchModelH
