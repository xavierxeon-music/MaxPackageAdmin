#include "HelpEditMessage.h"

#include <ChildrenSignalBlocker.h>

Help::Edit::Message::Message(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , messageName()
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());
   keyInfo->setText("MESSAGE");
}

void Help::Edit::Message::componentSelected(PatchParser::Marker marker, QVariant data)
{
   if (this->marker != marker)
      return;

   messageName = data.toString();
   const PatchStructure::Message& message = persona->parserRef().messageFreeMap.value(messageName);

   ChildrenSignalBlocker blocker(this);

   keyInfo->setText("MESSAGE " + persona->getCurrentKey());
   digestEdit->setText(message.digest.text);
   descrptionEdit->setPlainText(message.digest.description);

   highlighter->rehighlight(); // because signals are blocked
   qDebug() << __FUNCTION__ << "end";
}
