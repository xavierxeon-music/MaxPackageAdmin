#ifndef PersonaH
#define PersonaH

#include <QWidget>

#include <QStatusBar>
#include <QToolBar>

class MainWidget;

class Persona : public QWidget
{
   Q_OBJECT
public:
   Persona(MainWidget* mainWidget, const QString& name);

protected:
   QToolBar* getToolBar();

protected:
   MainWidget* mainWidget;

private:
   const QString& name;
   QToolBar* toolBar;
};

#endif // NOT PersonaH
