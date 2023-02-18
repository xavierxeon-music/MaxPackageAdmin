#ifndef MessageBarH
#define MessageBarH

#include <QTreeWidget>

class MessageWidget : public QTreeWidget
{
   Q_OBJECT
public:
   MessageWidget(QWidget* parent);
};

#endif // NOT MessageBarH
