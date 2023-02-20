#include "HelpEditContainer.h"

#include "HelpPersona.h"

#include "HelpEditArgument.h"
#include "HelpEditAttribute.h"
#include "HelpEditMessage.h"
#include "HelpEditOutput.h"
#include "HelpEditPatch.h"

Help::Edit::Container::Container(Persona* persona)
   : QStackedWidget(persona)
   , Persona::FunctionHub()
   , persona(persona)
   , editorMap()
{
   addEditor<Argument>(PatchStructure::Marker::Argument);
   addEditor<Attribute>(PatchStructure::Marker::Attribute);
   addEditor<Message>(PatchStructure::Marker::Message);
   addEditor<Output>(PatchStructure::Marker::Output);
   addEditor<Patch>(PatchStructure::Marker::Patch);
}

template <typename EditorType>
void Help::Edit::Container::addEditor(const PatchStructure::Marker& marker)
{
   Abstract* abstract = new EditorType(persona, marker);
   addWidget(abstract);

   editorMap[marker] = abstract;
}

void Help::Edit::Container::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   Q_UNUSED(data);

   setCurrentWidget(editorMap[marker]);
}
