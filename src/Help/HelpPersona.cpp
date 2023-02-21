#include "HelpPersona.h"

#include <QFile>
#include <QHBoxLayout>

#include "HelpComponentsModel.h"
#include "HelpComponentsView.h"
#include "HelpEditContainer.h"
#include "HelpSelectModel.h"
#include "HelpSelectView.h"

void Help::Persona::FunctionHub::patchSelected(QString patchPath, QString key)
{
   // do nothing
   Q_UNUSED(patchPath)
   Q_UNUSED(key)
}

void Help::Persona::FunctionHub::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   // do nothing
   Q_UNUSED(marker)
   Q_UNUSED(data)
}

// persoma

Help::Persona::Persona(MainWidget* mainWidget)
   : Abstract::Persona(mainWidget, "HELP")
   , Central::FunctionHub()
   , selectModel(nullptr)
   , componentsModel(nullptr)
   , structureMap()
{
   selectModel = new SelectModel(this);
   componentsModel = new ComponentsModel(this);

   SelectView* selectView = new SelectView(this, selectModel);
   ComponentsView* componentsView = new ComponentsView(this, componentsModel);
   Edit::Container* editorContainer = new Edit::Container(this);

   addWidget(selectView, "select");
   addWidget(componentsView, "components");
   addWidget(editorContainer, "edit");

   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload", this, &Persona::slotReload);
   QAction* saveAction = getToolBar()->addAction(QIcon(":/Save.svg"), "Save", this, &Persona::slotSave);
   saveAction->setShortcut(QKeySequence::Save);
}

void Help::Persona::buildPatchStructure(QString patchPath, const QString& key)
{
   if (!structureMap.contains(key))
      structureMap[key] = PatchStructure(patchPath);
}

Help::PatchStructure* Help::Persona::patchStructureRef(const QString& key)
{
   return &structureMap[key];
}

void Help::Persona::savePatchStructures()
{
   for (PatchStructure& patchStructure : structureMap)
      patchStructure.writeXML();

   callOnAllHubInstances(&Persona::setModified, false);
}

void Help::Persona::slotReload()
{
}

void Help::Persona::slotSave()
{
   savePatchStructures();
}
