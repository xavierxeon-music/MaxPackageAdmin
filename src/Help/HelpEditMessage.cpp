#include "HelpEditMessage.h"

Help::Edit::Message::Message(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , messageName()
{
   setupUi(this);
}

void Help::Edit::Message::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   messageName = data.toString();
   const PatchStructure::Message& message = persona->parser().messageMap[messageName];
}
