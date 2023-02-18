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

   QToolBar* mainToolBar = addToolBar("Main");
   mainToolBar->setMovable(false);

   centralStackWidget = new QStackedWidget(this);
   setCentralWidget(centralStackWidget);

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

   overviewPersona = new Overview::Persona(this);
   helpPersona = new Help::Persona(this);

   {
      Settings widgetSettings("MainWidget");
      restoreGeometry(widgetSettings.bytes("Geometry"));
   }

   Abstract::Persona::initAll();
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
