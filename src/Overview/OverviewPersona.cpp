#include "OverviewPersona.h"

#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>

#include "Settings.h"

#include "PackageView.h"
#include "PatchRawView.h"

Overview::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "OVER\nVIEW")
   , packageModel(nullptr)
   , patchRawModel(nullptr)
{
   packageModel = new Package::Model(this);
   patchRawModel = new Patch::RawModel(this);

   Package::View* packageView = new Package::View(this, packageModel);
   Patch::RawView* patchView = new Patch::RawView(this, patchRawModel);
   connect(packageView, &Package::View::signalPatchSelected, patchRawModel, &Patch::RawModel::slotSetPatch);

   QHBoxLayout* masterLayout = new QHBoxLayout(this);
   masterLayout->setContentsMargins(0, 0, 0, 0);
   masterLayout->addWidget(packageView);
   masterLayout->addWidget(patchView);

   QAction* openAction = getToolBar()->addAction(QIcon(":/Open.svg"), "Open", this, &Persona::slotOpenPackage);
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

void Overview::Persona::slotOpenPackage()
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
