#include "HelpEditArgument.h"

Help::Edit::Argument::Argument(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , argumentIndex()
{
   setupUi(this);
}

void Help::Edit::Argument::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   argumentIndex = data.toInt();
   const PatchStructure::Argument& argument = persona->parser().argumentList.at(argumentIndex);
}
