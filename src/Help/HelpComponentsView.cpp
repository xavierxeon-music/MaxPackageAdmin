#include "HelpComponentsView.h"

#include "HelpComponentsModel.h"
#include "HelpPatchStructure.h"

Help::ComponentsView::ComponentsView(QWidget* parent, ComponentsModel* model)
   : Abstract::ItemTreeView(parent, model)
   , Persona::FunctionHub()
{
   setHeaderHidden(true);
}

void Help::ComponentsView::clicked(ModelItem* item)
{
   const QVariant markerVariant = item->data(PatchStructure::RoleMarker);
   if (!markerVariant.isValid())
      return;

   const PatchStructure::Marker marker = markerVariant.value<PatchStructure::Marker>();

   const QVariant data = item->data(PatchStructure::RoleData);

   callOnAllHubInstances(&ComponentsView::componentSelected, marker, data);
}
