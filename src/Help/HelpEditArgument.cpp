#include "HelpEditArgument.h"

Help::Edit::Argument::Argument(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
   , argumentIndex()
{
   setupUi(this);
}

void Help::Edit::Argument::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   argumentIndex = data.toInt();
   const PatchStructure::Argument& argument = structureRef().argumentList.at(argumentIndex);
}
