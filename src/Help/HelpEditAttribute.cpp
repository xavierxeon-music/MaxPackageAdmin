#include "HelpEditAttribute.h"

Help::Edit::Attribute::Attribute(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}

