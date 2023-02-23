#include "HelpEditArgument.h"

#include <ChildrenSignalBlocker.h>

Help::Edit::Argument::Argument(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , argumentIndex()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());
   keyInfo->setText("ARGUMENT");
}

void Help::Edit::Argument::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   argumentIndex = data.toInt();
   const PatchStructure::Argument& argument = persona->parserRef().argumentList.at(argumentIndex);
   keyInfo->setText("ARGUMENT " + persona->getCurrentKey());

   ChildrenSignalBlocker blocker(this);

   digestEdit->setText(argument.digest.text);
   descrptionEdit->setPlainText(argument.digest.description);

   highlighter->rehighlight(); // because signals are blocked
   qDebug() << __FUNCTION__ << "end";
}
