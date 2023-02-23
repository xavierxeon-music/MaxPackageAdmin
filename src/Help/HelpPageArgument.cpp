#include "HelpPageArgument.h"

#include <ChildrenSignalBlocker.h>

Help::Page::Argument::Argument(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , argumentIndex()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());

   keyInfo->setText("ARGUMENT");
}

void Help::Page::Argument::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (editMarker != marker)
      return;

   argumentIndex = data.toInt();
   const PatchStructure::Argument& argument = persona->parserRef().argumentList.at(argumentIndex);
   keyInfo->setText("argument " + QString::number(argumentIndex) + " @ " + persona->getCurrentKey());

   ChildrenSignalBlocker blocker(this);

   digestEdit->setText(argument.digest.text);
   descrptionEdit->setPlainText(argument.digest.description);

   highlighter->rehighlight();
}
