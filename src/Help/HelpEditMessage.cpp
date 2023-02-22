#include "HelpEditMessage.h"

Help::Edit::Message::Message(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
   , messageName()
{
   setupUi(this);
}

void Help::Edit::Message::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   messageName = data.toString();
   const PatchStructure::Message& message = structureRef().messageMap[messageName];
}
