#include "HelpPageOutput.h"

#include <ChildrenSignalBlocker.h>

Help::Page::Output::Output(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , outputIndex()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());

   keyInfo->setText("OUTPUT");
}

void Help::Page::Output::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (editMarker != marker)
      return;

   outputIndex = data.toInt();
   const PatchStructure::Output& output = persona->parserRef().outputMap.value(outputIndex);

   ChildrenSignalBlocker blocker(this);

   keyInfo->setText("OUTPUT " + persona->getCurrentKey());
   descrptionEdit->setPlainText(output.digest.description);

   highlighter->rehighlight();
}
