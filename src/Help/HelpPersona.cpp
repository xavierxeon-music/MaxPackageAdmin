#include "HelpPersona.h"

#include <QHBoxLayout>

#include <AbstractItemTreeView.h>

#include "HelpFileModel.h"
#include "HelpFileView.h"
#include "HelpPatchModel.h"
#include "HelpPatchView.h"
#include "HelpSelectModel.h"
#include "HelpSelectView.h"

void Help::Persona::FunctionHub::patchSelected(QString patchPath)
{
   // do nothing
   Q_UNUSED(patchPath)
}

// persoma

Help::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "HELP")
   , selectModel(nullptr)
   , patchModel(nullptr)
   , fileModel(nullptr)
{
   selectModel = new SelectModel(this);
   patchModel = new PatchModel(this);
   fileModel = new FileModel(this);

   SelectView* selectView = new SelectView(this, selectModel);
   PatchView* patchView = new PatchView(this, patchModel);
   FileView* fileView = new FileView(this, fileModel);

   QHBoxLayout* masterLayout = new QHBoxLayout(this);
   masterLayout->setContentsMargins(0, 0, 0, 0);
   masterLayout->addWidget(selectView);
   masterLayout->addWidget(patchView);
   masterLayout->addWidget(fileView);

   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload");
}
