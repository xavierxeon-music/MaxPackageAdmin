#include "HelpEditOutput.h"

#include <ChildrenSignalBlocker.h>

Help::Edit::Output::Output(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , outputIndex()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());
   keyInfo->setText("OUTPUT");
}

void Help::Edit::Output::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   outputIndex = data.toInt();
   const PatchStructure::Output& output = persona->parserRef().outputMap.value(outputIndex);

   ChildrenSignalBlocker blocker(this);

   keyInfo->setText("OUTPUT " + persona->getCurrentKey());
   descrptionEdit->setPlainText(output.digest.description);

   highlighter->rehighlight(); // because signals are blocked
   qDebug() << __FUNCTION__ << "end";
}
