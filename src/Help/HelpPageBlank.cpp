#include "HelpPageBlank.h"

Help::Page::Blank::Blank(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);
}

void Help::Page::Blank::componentSelected(PatchParser::Marker marker, QVariant data)
{
   Q_UNUSED(marker)
   Q_UNUSED(data)
   // do nothing
}
