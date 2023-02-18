#ifndef HelpPatchModelH
#define HelpPatchModelH

#include <QStandardItemModel>

namespace Help
{
   class PatchModel : public QStandardItemModel
   {
      Q_OBJECT
   public:
      PatchModel(QObject* parent);
   };
} // namespace Help

#endif // NOT HelpPatchModelH
