#ifndef MainWidgetH
#define MainWidgetH

#include <QMainWindow>

#include <QStackedWidget>

#include "Help/HelpWidget.h"
#include "Main/TabToolBar.h"
#include "Overview/OverviewWidget.h"

class MainWidget : public QMainWindow
{
   Q_OBJECT
public:
   MainWidget();

private:
   using ToolBarMap = QMap<int, QToolBar*>;
   friend class PersonaWindow;
   friend class TabToolBar;

private slots:
   void slotUpdateTitle();

private:
   void closeEvent(QCloseEvent* ce) override;

private:
   // admin
   TabToolBar* tabToolBar;
   ToolBarMap toolBarMap;
   QStackedWidget* centralStackWidget;
   // content
   OverviewWidget* overviewPersona;
   HelpWidget* helpPersona;
};

#endif // NOT MainWidgetH
