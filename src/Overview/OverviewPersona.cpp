#include "OverviewPersona.h"

#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>

#include "Settings.h"

#include "PackageView.h"
#include "PatchView.h"

OverviewPersona::OverviewPersona(MainWidget* mainWidget)
   : Persona(mainWidget, "OVER\nVIEW")
   , packageModel(nullptr)
   , patchModel(nullptr)
{
   packageModel = new Package::Model(this);
   patchModel = new Patch::Model(this);

   Package::View* packageView = new Package::View(this, packageModel);

   Patch::View* patchView = new Patch::View(this);
   patchView->setModel(patchModel);

   connect(packageView, &Package::View::signalPatchSelected, patchModel, &Patch::Model::slotSetPatch);

   QHBoxLayout* masterLayout = new QHBoxLayout(this);
   masterLayout->setContentsMargins(0, 0, 0, 0);
   masterLayout->addWidget(packageView);
   masterLayout->addWidget(patchView);

   QAction* openAction = getToolBar()->addAction(QIcon(":/Open.svg"), "Open", this, &OverviewPersona::slotOpenPackage);
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
