#include "HelpEditPatch.h"

#include <ChildrenSignalBlocker.h>

Help::Edit::Patch::Patch(Persona* persona, const PatchStructure::Marker& marker)
   : Abstract(persona, marker)
{
   setupUi(this);

   connect(digestEdit, &QLineEdit::textChanged, this, &Patch::slotChangeDigest);
   connect(descrptionEdit, &QPlainTextEdit::textChanged, this, &Patch::slotChangeDescription);
}

void Help::Edit::Patch::slotChangeDigest()
{
   structureRef()->patchDigest.text = digestEdit->text();
   markModified();
}

void Help::Edit::Patch::slotChangeDescription()
{
   structureRef()->patchDigest.description = descrptionEdit->toPlainText();
   markModified();
}

void Help::Edit::Patch::componentSelected(PatchStructure::Marker marker, QVariant data)
{
   Q_UNUSED(data)

   if (this->marker != marker)
      return;

   ChildrenSignalBlocker blocker(this);

   digestEdit->setText(structureRef()->patchDigest.text);
   descrptionEdit->setPlainText(structureRef()->patchDigest.description);
}
