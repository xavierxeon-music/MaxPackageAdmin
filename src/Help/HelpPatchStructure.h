#ifndef HelpPatchStructureH
#define HelpPatchStructureH

#include <PatchStructure.h>

#include <QDomElement>
#include <QMap>

namespace Help
{
   class PatchStructure : public ::PatchStructure
   {
   public:
      PatchStructure();
      PatchStructure(const QString& patchPath);

   public:
      void writeXML();

   private:
      void readXML();
      void addJSON();

   private:
      QString patchName;
      QString patchPath;
      QString helpPath;
   };
} // namespace Help

#endif // NOT HelpPatchStructureH
