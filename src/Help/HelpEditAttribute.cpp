#include "HelpEditAttribute.h"

#include <ChildrenSignalBlocker.h>

Help::Edit::Attribute::Attribute(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , attributeName()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());
   keyInfo->setText("ATTRIBUTE");
}

void Help::Edit::Attribute::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   attributeName = data.toString();
   const PatchStructure::Attribute& attribute = persona->parserRef().attributeMap.value(attributeName);
   keyInfo->setText("ATTRIBUTE " + persona->getCurrentKey());

   ChildrenSignalBlocker blocker(this);

   digestEdit->setText(attribute.digest.text);
   descrptionEdit->setPlainText(attribute.digest.description);

   highlighter->rehighlight(); // because signals are blocked
}
