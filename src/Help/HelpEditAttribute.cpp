#include "HelpEditAttribute.h"

Help::Edit::Attribute::Attribute(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , attributeName()
{
   setupUi(this);
}

void Help::Edit::Attribute::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   attributeName = data.toString();
   const PatchStructure::Attribute& attribute = persona->structure().attributeMap[attributeName];
}
