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
   addEditor<Argument>(PatchParser::Marker::Argument);
   addEditor<Attribute>(PatchParser::Marker::Attribute);
   addEditor<Message>(PatchParser::Marker::Message);
   addEditor<Output>(PatchParser::Marker::Output);
   addEditor<Patch>(PatchParser::Marker::Patch);
}

template <typename EditorType>
void Help::Edit::Container::addEditor(const PatchParser::Marker& marker)
{
   Abstract* abstract = new EditorType(persona, marker);
   addWidget(abstract);

   editorMap[marker] = abstract;
}

void Help::Edit::Container::componentSelected(PatchParser::Marker marker, QVariant data)
{
   Q_UNUSED(data);

   if (!editorMap.contains(marker))
      return;

   setCurrentWidget(editorMap.value(marker));
}
