#include "OverviewPersona.h"

#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>

#include <Settings.h>

#include "OverviewPackageModel.h"
#include "OverviewPackageView.h"
#include "OverviewPatchModel.h"

// function hub

void Overview::Persona::FunctionHub::patchSelected(QString patchPath)
{
   // do nothing
   Q_UNUSED(patchPath)
}

// presona

Overview::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "OVER\nVIEW")
   , Central::FunctionHub()
   , packageModel(nullptr)
   , patchModel(nullptr)
{
   packageModel = new PackageModel(this);
   patchModel = new PatchModel(this);

   PackageView* packageView = new PackageView(this, packageModel);
   Abstract::ItemTreeView* patchView = new Abstract::ItemTreeView(this, patchModel);

   addWidget(packageView, "files");
   addWidget(patchView, "patch");

   getToolBar()->addAction(QIcon(":/Open.svg"), "Open", this, &Persona::slotOpenPackage);
}

void Overview::Persona::slotOpenPackage()
{
   const QString fileName = QFileDialog::getOpenFileName(this, "package", QString(), "package-info.json");
   if (fileName.isEmpty())
      return;

   const QString packagePath = QFileInfo(fileName).absolutePath();

   {
      Settings settings;
      settings.write("LastPackage", packagePath);
      callOnAllHubInstances(&Persona::setPackagePath, packagePath);
   }
}

void Overview::Persona::laodState()
{
   Abstract::Persona::laodState();

   const QString packagePath = Central::getPackagePath();
   if (!packagePath.isEmpty())
   {
      callOnAllHubInstances(&Persona::setPackagePath, packagePath);
   }
}
