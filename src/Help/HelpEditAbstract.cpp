#include "HelpEditAbstract.h"

#include "HelpPersona.h"

Help::Edit::Abstract::Abstract(Persona* persona, const PatchParser::Marker& marker)
   : QWidget(persona)
   , Persona::FunctionHub()
   , Central::FunctionHub()
   , persona(persona)
   , marker(marker)

{
}

Help::Edit::Abstract::~Abstract()
{
}
