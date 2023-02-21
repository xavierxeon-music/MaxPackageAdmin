#include "HelpEditAbstract.h"

#include "HelpPersona.h"

Help::Edit::Abstract::Abstract(Persona* persona, const PatchStructure::Marker& marker)
   : QWidget(persona)
   , Persona::FunctionHub()
   , persona(persona)
   , key()
   , marker(marker)
{
}

Help::Edit::Abstract::~Abstract()
{
}

Help::PatchStructure* Help::Edit::Abstract::structureRef()
{
   return structureRef();
}

void Help::Edit::Abstract::patchSelected(QString patchPath, QString key)
{
   Q_UNUSED(patchPath)
   this->key = key;
}
