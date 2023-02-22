#include "HelpEditOutput.h"

Help::Edit::Output::Output(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
   , outputIndex()
{
   setupUi(this);
}

void Help::Edit::Output::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   outputIndex = data.toInt();
   const PatchStructure::Output& output = persona->structure().outputMap[outputIndex];
}
