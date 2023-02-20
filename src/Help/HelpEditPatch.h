#ifndef HelpEditPatchH
#define HelpEditPatchH

#include "HelpEditAbstract.h"
#include "ui_HelpEditPatch.h"

namespace Help
{
   namespace Edit
   {
      class Patch : public Abstract, private Ui::Patch
      {
         Q_OBJECT

      public:
         Patch(Persona* persona, const PatchStructure::Marker& marker);
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditPatchH
