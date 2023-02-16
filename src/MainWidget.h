#ifndef MainWidgetH
#define MainWidgetH

#include <QWidget>

#include "Help/HelpWidget.h"
#include "Overview/OverviewWidget.h"

class MainWidget : public QWidget
{
   Q_OBJECT
public:
   MainWidget();

private:
   void closeEvent(QCloseEvent* ce) override;

private:
   OverviewWidget* overviewWidget;
   HelpWidget* helpWidget;
};

#endif // NOT MainWidgetH
