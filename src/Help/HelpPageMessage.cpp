#include "HelpPageMessage.h"

#include <ChildrenSignalBlocker.h>

Help::Page::Message::Message(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , messageName()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());

   keyInfo->setText("MESSAGE");
}

void Help::Page::Message::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (editMarker != marker)
      return;

   messageName = data.toString();
   const PatchStructure::Message& message = persona->parserRef().messageFreeMap.value(messageName);

   ChildrenSignalBlocker blocker(this);

   keyInfo->setText("MESSAGE " + persona->getCurrentKey());
   digestEdit->setText(message.digest.text);
   descrptionEdit->setPlainText(message.digest.description);

   highlighter->rehighlight();
}
