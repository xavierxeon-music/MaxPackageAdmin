#ifndef PersonaWindowH
#define PersonaWindowH

#include <QMainWindow>

class MainWidget;

class PersonaWindow : public QMainWindow
{
   Q_OBJECT
public:
   PersonaWindow(MainWidget* mainWidget);

protected:
   MainWidget* mainWidget;
};

#endif // NOT PersonaWindowH
