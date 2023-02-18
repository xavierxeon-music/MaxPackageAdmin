#include "OverviewPersona.h"

#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>

#include "Settings.h"

#include "OverviewPackageModel.h"
#include "OverviewPackageView.h"
#include "OverviewPatchModel.h"
#include "OverviewPatchView.h"

// function hub

Overview::FunctionHub::FunctionHub()
   : Abstract::FunctionHub<Persona>()
{
}

void Overview::FunctionHub::patchSelected(QString patchPath)
{
   // do nothing
   Q_UNUSED(patchPath)
}

// presona

Overview::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "OVER\nVIEW")
   , packageModel(nullptr)
   , patchModel(nullptr)
{
   packageModel = new PackageModel(this);
   patchModel = new PatchModel(this);

   PackageView* packageView = new PackageView(this, packageModel);
   PatchView* patchView = new PatchView(this, patchModel);

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
