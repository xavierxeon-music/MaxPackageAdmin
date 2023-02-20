#include "HelpEditOutput.h"

Help::Edit::Output::Output(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}
