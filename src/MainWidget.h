#ifndef MainWidgetH
#define MainWidgetH

#include <QMainWindow>

#include <QStackedWidget>

#include "Help/HelpPersona.h"
#include "Main/TabToolBar.h"
#include "Overview/OverviewPersona.h"

class MainWidget : public QMainWindow
{
   Q_OBJECT
public:
   MainWidget();

private:
   using ToolBarMap = QMap<int, QToolBar*>;
   friend class Abstract::Persona;
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
   Overview::Persona* overviewPersona;
   Help::Persona* helpPersona;
};

#endif // NOT MainWidgetH
