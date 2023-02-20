#include "HelpEditArgument.h"

Help::Edit::Argument::Argument(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}

