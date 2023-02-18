#ifndef HelpFileModelH
#define HelpFileModelH

#include <QStandardItemModel>

namespace Help
{
   class FileModel : public QStandardItemModel
   {
      Q_OBJECT
   public:
      FileModel(QObject* parent);
   };
} // namespace Help

#endif // NOT HelpFileModelH
