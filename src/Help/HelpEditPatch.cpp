#include "HelpEditPatch.h"

Help::Edit::Patch::Patch(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}

void Help::Edit::Patch::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   Q_UNUSED(data)

   if (this->marker != marker)
      return;
}
