#include "MainWidget.h"

#include <QApplication>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "Settings.h"

static const int sideBarHeight = 48;

MainWidget::MainWidget()
   : QWidget(nullptr)
   , buttonGroup(nullptr)
   , stackLayout(nullptr)
   , toolBarLayout(nullptr)
   , toolBarSeperator(nullptr)
   , toolBarMap()
   , overviewPersona(nullptr)
   , helpPersona(nullptr)
{
   setWindowTitle("Max Package Admin");

   // side bar
   {
      buttonGroup = new QButtonGroup(this);
      connect(buttonGroup, &QButtonGroup::idClicked, this, &MainWidget::slotChangePersona);

      toolBarSeperator = new QWidget(this);
      toolBarSeperator->setFixedSize(20, sideBarHeight);
      toolBarSeperator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

      QWidget* spacer = new QWidget(this);
      spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

      QLabel* iconLabel = new QLabel(this);
      iconLabel->setPixmap(QPixmap(":/MPA.svg").scaled(sideBarHeight, sideBarHeight));

      toolBarLayout = new QHBoxLayout();
      toolBarLayout->setContentsMargins(0, 0, 0, 0);
      toolBarLayout->setSpacing(0);
      toolBarLayout->addWidget(toolBarSeperator);
      toolBarLayout->addWidget(spacer);
      toolBarLayout->addWidget(iconLabel);
   }

   // main area
   {
      stackLayout = new QStackedLayout();
      stackLayout->setContentsMargins(0, 0, 0, 0);

      QVBoxLayout* masterLayout = new QVBoxLayout(this);
      masterLayout->setContentsMargins(5, 5, 5, 5);
      masterLayout->addLayout(toolBarLayout);
      masterLayout->addLayout(stackLayout);
   }

   overviewPersona = new OverviewWidget(this);
   helpPersona = new HelpWidget(this);

   connect(overviewPersona, &OverviewWidget::signalUpdateTitle, this, &MainWidget::slotUpdateTitle);
   slotUpdateTitle();

   {
      Settings widgetSettings("MainWidget");
      restoreGeometry(widgetSettings.bytes("Geometry"));
   }

   slotChangePersona(0);
}

void MainWidget::addPersona(PersonaWindow* payload, QToolBar* toolBar, const QString& name)
{
   QPushButton* button = new QPushButton(this);
   button->setFixedSize(sideBarHeight, sideBarHeight);
   button->setText(name);

   int buttonIindex = [&]()
   {
      for (int searchIndex = 0; searchIndex < toolBarLayout->count(); searchIndex++)
      {
         const QWidget* widget = toolBarLayout->itemAt(searchIndex)->widget();
         if (widget == toolBarSeperator)
            return searchIndex;
      }

      return 0;
   }();

   toolBarLayout->insertWidget(buttonIindex, button);
   buttonGroup->addButton(button, buttonIindex);

   toolBar->setFixedHeight(sideBarHeight);
   toolBar->setMovable(false);
   toolBar->setOrientation(Qt::Horizontal);
   toolBarLayout->insertWidget(buttonIindex + 2, toolBar);
   toolBarMap[buttonIindex] = toolBar;

   stackLayout->addWidget(payload);
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

void MainWidget::slotChangePersona(int index)
{
   stackLayout->setCurrentIndex(index);

   for (ToolBarMap::Iterator it = toolBarMap.begin(); it != toolBarMap.end(); it++)
   {
      QToolBar* toolBar = it.value();
      toolBar->setVisible(it.key() == index);
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
