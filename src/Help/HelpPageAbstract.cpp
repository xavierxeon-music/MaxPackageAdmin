#include "HelpPageAbstract.h"

#include "HelpPersona.h"

Help::Page::Abstract::Abstract(Persona* persona, const PatchParser::Marker& marker)
   : QWidget(persona)
   , Persona::FunctionHub()
   , Central::FunctionHub()
   , persona(persona)
   , editMarker(marker)
{
}

Help::Page::Abstract::~Abstract()
{
}
