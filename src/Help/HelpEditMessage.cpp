#include "HelpEditMessage.h"

Help::Edit::Message::Message(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}

