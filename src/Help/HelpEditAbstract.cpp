#include "HelpEditAbstract.h"

#include "HelpPersona.h"

Help::Edit::Abstract::Abstract(Persona* persona, const PatchStructure::Marker& marker)
   : QWidget(persona)
   , Persona::FunctionHub()
   , Central::FunctionHub()
   , persona(persona)
   , key()
   , marker(marker)
{
}

Help::Edit::Abstract::~Abstract()
{
}

const Help::PatchStructure& Help::Edit::Abstract::structure() const
{
   return *(persona->patchStructureRef(key));
}

Help::PatchStructure& Help::Edit::Abstract::structureRef()
{
   return *(persona->patchStructureRef(key));
}

void Help::Edit::Abstract::patchSelected(QString patchPath, QString key)
{
   Q_UNUSED(patchPath)
   this->key = key;
}
