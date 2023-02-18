#ifndef HelpSelectModelH
#define HelpSelectModelH

#include <QStandardItemModel>

namespace Help
{
   class SelectModel : public QStandardItemModel
   {
      Q_OBJECT
   public:
      SelectModel(QObject* parent);
   };
} // namespace Help

#endif // NOT HelpSelectModelH
