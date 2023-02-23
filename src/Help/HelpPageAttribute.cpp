#include "HelpPageAttribute.h"

#include <ChildrenSignalBlocker.h>

Help::Page::Attribute::Attribute(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , attributeName()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());

   keyInfo->setText("ATTRIBUTE");
}

void Help::Page::Attribute::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (editMarker != marker)
      return;

   attributeName = data.toString();
   const PatchStructure::Attribute& attribute = persona->parserRef().attributeMap.value(attributeName);
   keyInfo->setText("attribute " + attributeName + " @ " + persona->getCurrentKey());

   ChildrenSignalBlocker blocker(this);

   digestEdit->setText(attribute.digest.text);
   descrptionEdit->setPlainText(attribute.digest.description);

   highlighter->rehighlight();
}
