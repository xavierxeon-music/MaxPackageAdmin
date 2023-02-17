#ifndef PersonaWindowH
#define PersonaWindowH

#include <QWidget>

#include <QStatusBar>
#include <QToolBar>

class MainWidget;

class PersonaWindow : public QWidget
{
   Q_OBJECT
public:
   PersonaWindow(MainWidget* mainWidget, const QString& name);

protected:
   QToolBar* getToolBar();

protected:
   MainWidget* mainWidget;

private:
   const QString& name;
   QToolBar* toolBar;
};

#endif // NOT PersonaWindowH
