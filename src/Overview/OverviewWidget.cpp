#include "OverviewWidget.h"

#include <QLabel>

#include <QAction>

#include <QFileDialog>
#include <QToolBar>

#include "Settings.h"

#include "PackageView.h"

OverviewWidget::OverviewWidget(MainWidget* mainWidget)
   : PersonaWindow(mainWidget)
   , packageModel(nullptr)
{
   packageModel = new Package::Model(this);

   Package::View* packageView = new Package::View(this);
   packageView->setModel(packageModel);
   setLeftDock(packageView);

   setCentralWidget(new QLabel("OVERVIEW"));

   // toolbars and menus
   QToolBar* packageBar = addToolBar("Package");
   packageBar->setMovable(false);

   QAction* openAction = packageBar->addAction(QIcon(":/Open.svg"), "Open", this, &OverviewWidget::slotOpenPackage);
   Q_UNUSED(openAction)

   // restore settings
   {
      Settings settings;
      const QString packageDir = settings.string("LastPackage");
      if (!packageDir.isEmpty())
      {
         packageModel->setPath(packageDir);
         emit signalUpdateTitle();
      }
   }
}

void OverviewWidget::slotOpenPackage()
{
   const QString fileName = QFileDialog::getOpenFileName(this, "package", QString(), "package-info.json");
   if (fileName.isEmpty())
      return;

   const QString packageDir = QFileInfo(fileName).absolutePath();

   {
      Settings settings;
      settings.write("LastPackage", packageDir);
      packageModel->setPath(packageDir);
   }

   emit signalUpdateTitle();
}
