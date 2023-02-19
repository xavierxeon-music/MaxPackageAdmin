#include "HelpPatchStructure.h"

Help::PatchStructure::PatchStructure()
   : PatchStructure(QString(), QString())
{
}

Help::PatchStructure::PatchStructure(const QString& patchPath, const QString& helpPath)
   : patchPath(patchPath)
   , helpPath(helpPath)
{
}
