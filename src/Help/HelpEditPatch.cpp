#include "HelpEditPatch.h"

Help::Edit::Patch::Patch(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}

