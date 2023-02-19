#include "MainWidget.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDockWidget>
#include <QLabel>

#include "Message.h"
#include "Settings.h"

#ifdef Q_OS_MACX
#include "Main/MacTheme.h"
#endif // Q_OS_MACX

MainWidget::MainWidget()
   : QMainWindow(nullptr)
   , Central::FunctionHub()
   , tabToolBar(nullptr)
   , toolBarMap()
   , centralStackWidget(nullptr)
   , overviewPersona(nullptr)
   , helpPersona(nullptr)
{
   setWindowTitle("Max Package Admin");

   tabToolBar = new TabToolBar(this);
   addToolBar(tabToolBar);

   centralStackWidget = new QStackedWidget(this);
   setCentralWidget(centralStackWidget);

   helpPersona = new Help::Persona(this);
   overviewPersona = new Overview::Persona(this);

   QToolBar* mainToolBar = addToolBar("Main");
   mainToolBar->setMovable(false);
   QWidget* spacer = new QWidget(this);
   spacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
   mainToolBar->addWidget(spacer);

   // message dock
   {
      QDockWidget* messageDock = new QDockWidget(this);
      messageDock->setWidget(new Message::Widget(this));
      messageDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
      messageDock->setTitleBarWidget(new QWidget(this));
      addDockWidget(Qt::BottomDockWidgetArea, messageDock);

      messageDock->hide();
      QAction* messageAction = mainToolBar->addAction(QIcon(":/Message.svg"), "Messages");
      messageAction->setCheckable(true);
      connect(messageAction, &QAction::toggled, messageDock, &QWidget::setVisible);
   }

   Settings widgetSettings("MainWidget");
   restoreGeometry(widgetSettings.bytes("Geometry"));

   Abstract::Persona::callOnAllInstances(&Abstract::Persona::laodState);

   tabToolBar->slotChangeTab(0);
}

void MainWidget::setPackagePath(QString packageDir)
{
   if (packageDir.isEmpty())
      setWindowTitle("Max Package Admin");
   else
      setWindowTitle("Max Package Admin - " + packageDir);
}

void MainWidget::closeEvent(QCloseEvent* ce)
{
   Settings widgetSettings("MainWidget");
   widgetSettings.write("Geometry", saveGeometry());

   Abstract::Persona::callOnAllInstances(&Abstract::Persona::saveState);

   ce->accept();
}

// main function

int main(int argc, char** argv)
{
   QApplication app(argc, argv);
#ifdef Q_OS_MACX
   MacTheme::dark();
#endif // Q_OS_MACX

   MainWidget mw;
   mw.show();

   return app.exec();
}
