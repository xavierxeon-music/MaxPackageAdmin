#include "HelpPersona.h"

#include <QFile>
#include <QHBoxLayout>

#include "HelpComponentsModel.h"
#include "HelpComponentsView.h"
#include "HelpEditWidget.h"
#include "HelpSelectModel.h"
#include "HelpSelectView.h"

void Help::Persona::FunctionHub::patchSelected(QString patchPath, QString key)
{
   // do nothing
   Q_UNUSED(patchPath)
   Q_UNUSED(key)
}

void Help::Persona::FunctionHub::componentSelected(PatchParser::Marker marker, QVariant data)
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
   , currentKey()
   , parserMap()
{
   selectModel = new SelectModel(this);
   componentsModel = new ComponentsModel(this);

   SelectView* selectView = new SelectView(this, selectModel);
   ComponentsView* componentsView = new ComponentsView(this, componentsModel);
   Edit::Widget* editWidget = new Edit::Widget(this);

   addWidget(selectView, "select");
   addWidget(componentsView, "components");
   addWidget(editWidget, "edit");

   getToolBar()->addAction(QIcon(":/Reload.svg"), "Reload", this, &Persona::slotReload);
   QAction* saveAction = getToolBar()->addAction(QIcon(":/Save.svg"), "Save", this, &Persona::slotSave);
   saveAction->setShortcut(QKeySequence::Save);
}

const QString& Help::Persona::getCurrentKey() const
{
   return currentKey;
}

Help::PatchParser Help::Persona::parser() const
{
   return parserMap[currentKey];
}

Help::PatchParser& Help::Persona::parserRef()
{
   return parserMap[currentKey];
}

void Help::Persona::buildPatchStructure(QString patchPath, const QString& key)
{
   currentKey = key;

   if (!parserMap.contains(key))
      parserMap[key] = PatchParser(patchPath);
}

void Help::Persona::savePatchStructures()
{
   for (PatchParser& parser : parserMap)
      parser.writeXML();

   callOnAllHubInstances(&Persona::setModified, false);
}

void Help::Persona::slotReload()
{
}

void Help::Persona::slotSave()
{
   savePatchStructures();
}
