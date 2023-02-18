#ifndef MessageBarH
#define MessageBarH

#include <QTreeWidget>

class MessageWidget : public QTreeWidget
{
   Q_OBJECT
public:
   MessageWidget(QWidget* parent);

public:
   static void info(const QString& message);
   static void warning(const QString& message);
   static void error(const QString& message);
};

#endif // NOT MessageBarH
