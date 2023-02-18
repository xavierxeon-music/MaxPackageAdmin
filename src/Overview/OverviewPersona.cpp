#include "OverviewPersona.h"

#include <QAction>
#include <QFileDialog>
#include <QVBoxLayout>

#include "Settings.h"

#include "PackageView.h"

OverviewPersona::OverviewPersona(MainWidget* mainWidget)
   : Persona(mainWidget, "OVER\nVIEW")
   , packageModel(nullptr)
{
   packageModel = new Package::Model(this);

   Package::View* packageView = new Package::View(this);
   packageView->setModel(packageModel);

   QAction* openAction = getToolBar()->addAction(QIcon(":/Open.svg"), "Open", this, &OverviewPersona::slotOpenPackage);
   Q_UNUSED(openAction)

   QVBoxLayout* masterLayout = new QVBoxLayout(this);
   masterLayout->setContentsMargins(0, 0, 0, 0);
   masterLayout->addWidget(packageView);

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

void OverviewPersona::slotOpenPackage()
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
