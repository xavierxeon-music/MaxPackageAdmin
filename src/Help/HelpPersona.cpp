#include "HelpPersona.h"

#include <QHBoxLayout>

#include <AbstractItemTreeView.h>

#include "HelpComponentsModel.h"
#include "HelpComponentsView.h"
#include "HelpFileModel.h"
#include "HelpFileView.h"
#include "HelpSelectModel.h"
#include "HelpSelectView.h"

void Help::Persona::FunctionHub::patchSelected(QString patchPath)
{
   const QFileInfo patchInfo(patchPath);
   const QString key = patchInfo.fileName().replace(".maxpat", "");
   const QString packagePath = Central::getPackagePath();

   const QString helpPath = packagePath + "/docs/" + key + ".maxref.xml";

   patchStructure = PatchStructure(patchPath, helpPath);
}

// persoma

Help::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "HELP")
   , selectModel(nullptr)
   , componentsModel(nullptr)
   , fileModel(nullptr)
{
   selectModel = new SelectModel(this);
   componentsModel = new ComponentsModel(this);
   fileModel = new FileModel(this);

   SelectView* selectView = new SelectView(this, selectModel);
   ComponentsView* componentsView = new ComponentsView(this, componentsModel);
   FileView* fileView = new FileView(this, fileModel);

   addWidget(selectView, "select");
   addWidget(componentsView, "components");
   addWidget(fileView, "description");

   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload");
}
