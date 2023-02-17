#ifndef MainWidgetH
#define MainWidgetH

#include <QWidget>

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QStackedLayout>

#include "Help/HelpWidget.h"
#include "Overview/OverviewWidget.h"

class MainWidget : public QWidget
{
   Q_OBJECT
public:
   MainWidget();

public:
   void addPersona(PersonaWindow* payload, QToolBar* toolBar, const QString& name);

private:
   using ToolBarMap = QMap<int, QToolBar*>;

private slots:
   void slotUpdateTitle();
   void slotChangePersona(int index);

private:
   void closeEvent(QCloseEvent* ce) override;

private:
   QButtonGroup* buttonGroup;
   QStackedLayout* stackLayout;
   QHBoxLayout* toolBarLayout;
   QWidget* toolBarSeperator;
   ToolBarMap toolBarMap;

   OverviewWidget* overviewPersona;
   HelpWidget* helpPersona;
};

#endif // NOT MainWidgetH
