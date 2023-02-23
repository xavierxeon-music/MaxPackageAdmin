#include "HelpEditPatch.h"

#include <QButtonGroup>

#include <ChildrenSignalBlocker.h>

Help::Edit::Patch::Patch(Persona* persona, const PatchParser::Marker& marker)
   : Abstract(persona, marker)
   , highlighter(nullptr)
   , standardMethodGroup(nullptr)
{
   setupUi(this);
   highlighter = new DescriptionHighlighter(descrptionEdit->document());
   keyInfo->setText("PATCH");

   standardMethodGroup = new QButtonGroup(this);
   standardMethodGroup->addButton(messageBangButton, static_cast<int>(PatchStructure::Type::Bang));
   standardMethodGroup->addButton(messageIntButton, static_cast<int>(PatchStructure::Type::Integer));
   standardMethodGroup->addButton(messageFloatButton, static_cast<int>(PatchStructure::Type::Float));
   standardMethodGroup->addButton(messageListButton, static_cast<int>(PatchStructure::Type::List));
   standardMethodGroup->addButton(messageSignalButton, static_cast<int>(PatchStructure::Type::Signal));

   connect(metaTagEdit, &QLineEdit::textChanged, this, &Patch::slotChangedMetaTag);
   connect(standardMethodGroup, &QButtonGroup::idClicked, this, &Patch::slotAddStandardMethond);
   connect(digestEdit, &QLineEdit::textChanged, this, &Patch::slotChangeDigest);
   connect(descrptionEdit, &QPlainTextEdit::textChanged, this, &Patch::slotChangeDescription);
   connect(seeAlsoEdit, &QLineEdit::textChanged, this, &Patch::slotChangeSeeAlso);
}

void Help::Edit::Patch::slotChangedMetaTag()
{
   const QStringList metaTageList = metaTagEdit->text().split(";");
   copyIfChanged(persona->parserRef().metaTagList, metaTageList);
}

void Help::Edit::Patch::slotAddStandardMethond(int type)
{
   qDebug() << __FUNCTION__ << type;
}

void Help::Edit::Patch::slotChangeDigest()
{
   copyIfChanged(persona->parserRef().patchDigest.text, digestEdit->text());
}

void Help::Edit::Patch::slotChangeDescription()
{
   copyIfChanged(persona->parserRef().patchDigest.description, descrptionEdit->toPlainText());
}

void Help::Edit::Patch::slotChangeSeeAlso()
{
   const QStringList seeAlsoList = seeAlsoEdit->text().split(";");
   copyIfChanged(persona->parserRef().seeAlsoList, seeAlsoList);
}

void Help::Edit::Patch::componentSelected(PatchParser::Marker marker, QVariant data)
{
   Q_UNUSED(data)

   if (this->marker != marker)
      return;

   ChildrenSignalBlocker blocker(this);

   keyInfo->setText("PATCH " + persona->getCurrentKey());
   metaTagEdit->setText(persona->parserRef().metaTagList.join(";"));
   digestEdit->setText(persona->parserRef().patchDigest.text);
   descrptionEdit->setPlainText(persona->parserRef().patchDigest.description);
   seeAlsoEdit->setText(persona->parserRef().seeAlsoList.join(";"));

   highlighter->rehighlight(); // because signals are blocked
   qDebug() << __FUNCTION__ << "end";
}
