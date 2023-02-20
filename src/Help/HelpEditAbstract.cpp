#include "HelpEditAbstract.h"

#include "HelpPersona.h"

Help::Edit::Abstract::Abstract(Persona* persona, const PatchStructure::Marker& marker)
   : QWidget(persona)
   , persona(persona)
   , marker(marker)
{
}

Help::Edit::Abstract::~Abstract()
{
}
