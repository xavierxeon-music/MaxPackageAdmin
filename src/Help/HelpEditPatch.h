#ifndef HelpEditPatchH
#define HelpEditPatchH

#include "HelpEditAbstract.h"
#include "ui_HelpEditPatch.h"

#include "HelpDescriptionHighlighter.h"

namespace Help
{
   namespace Edit
   {
      class Patch : public Abstract, private Ui::Patch
      {
         Q_OBJECT

      public:
         Patch(Persona* persona, const PatchParser::Marker& marker);

      private:
         void slotChangedMetaTag();
         void slotAddStandardMethond(int type);
         void slotChangeDigest();
         void slotChangeDescription();
         void slotChangeSeeAlso();

      private:
         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         DescriptionHighlighter* highlighter;
         QButtonGroup* standardMethodGroup;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditPatchH
