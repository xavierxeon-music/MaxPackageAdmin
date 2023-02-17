#include "MainWidget.h"

#include <QApplication>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "Settings.h"

#ifdef Q_OS_MACX
#include "Main/Mac.h"
#endif // Q_OS_MACX

MainWidget::MainWidget()
   : QMainWindow(nullptr)
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

   overviewPersona = new OverviewWidget(this);
   helpPersona = new HelpWidget(this);

   connect(overviewPersona, &OverviewWidget::signalUpdateTitle, this, &MainWidget::slotUpdateTitle);
   slotUpdateTitle();

   {
      Settings widgetSettings("MainWidget");
      restoreGeometry(widgetSettings.bytes("Geometry"));
   }

   tabToolBar->slotChangeTab(0);
}

void MainWidget::slotUpdateTitle()
{
   Settings settings;
   const QString packageDir = settings.string("LastPackage");

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
   Mac::setToDarkTheme();
#endif // Q_OS_MACX

   MainWidget mw;
   mw.show();

   return app.exec();
}
