#include "MainWidget.h"

#include <QApplication>
#include <QCloseEvent>
#include <QGridLayout>
#include <QStackedWidget>
#include <QTabBar>

#include "Settings.h"

MainWidget::MainWidget()
   : QWidget(nullptr)
   , overviewWidget(nullptr)
   , helpWidget(nullptr)
{
   setWindowTitle("Max Package Admin");

   QTabBar* tabBar = new QTabBar(this);
   QStackedWidget* stackWidget = new QStackedWidget(this);
   connect(tabBar, &QTabBar::currentChanged, stackWidget, &QStackedWidget::setCurrentIndex);

   auto addPersona = [&](PersonaWindow* persona, const QString& name)
   {
      tabBar->addTab(name);
      stackWidget->addWidget(persona);
   };

   overviewWidget = new OverviewWidget(this);
   addPersona(overviewWidget, "Overview");

   helpWidget = new HelpWidget(this);
   addPersona(helpWidget, "Help");

   QWidget* spacer = new QWidget(this);
   spacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

   QGridLayout* masterLayout = new QGridLayout(this);
   masterLayout->setContentsMargins(0, 0, 0, 0);
   masterLayout->addWidget(tabBar, 0, 0);
   masterLayout->addWidget(spacer, 0, 1);
   masterLayout->addWidget(stackWidget, 1, 0, 2, 1);

   {
      Settings widgetSettings("MainWidget");
      restoreGeometry(widgetSettings.bytes("Geometry"));
   }
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

   MainWidget mw;
   mw.show();

   return app.exec();
}
