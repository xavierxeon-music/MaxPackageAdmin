#include "HelpPersona.h"

#include <QFile>
#include <QHBoxLayout>

#include "HelpComponentEditor.h"
#include "HelpComponentsModel.h"
#include "HelpComponentsView.h"
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
   , componentsModel(nullptr)
   , patchStructure()
{
   selectModel = new SelectModel(this);
   componentsModel = new ComponentsModel(this);

   SelectView* selectView = new SelectView(this, selectModel);
   ComponentsView* componentsView = new ComponentsView(this, componentsModel);
   ComponentEditor* componentEditor = new ComponentEditor(this);

   addWidget(selectView, "select");
   addWidget(componentsView, "components");
   addWidget(componentEditor, "edit");

   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload");
}

void Help::Persona::buildPatchStructure(QString patchPath)
{
   patchStructure = PatchStructure(patchPath);
}

Help::PatchStructure* Help::Persona::patchStructureRef()
{
   return &patchStructure;
}

void Help::Persona::savePatchStructure()
{
      patchStructure.writeXML();
}
