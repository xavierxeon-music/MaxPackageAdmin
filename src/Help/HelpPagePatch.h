#ifndef HelpPagePatchH
#define HelpPagePatchH

#include "HelpPageAbstract.h"
#include "ui_HelpPagePatch.h"

#include "HelpDescriptionHighlighter.h"

namespace Help
{
   namespace Page
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

#endif // NOT HelpPagePatchH
