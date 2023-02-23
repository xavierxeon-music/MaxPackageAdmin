#ifndef HelpEditOutputH
#define HelpEditOutputH

#include "HelpEditAbstract.h"
#include "ui_HelpEditOutput.h"

#include "HelpDescriptionHighlighter.h"

namespace Help
{
   namespace Edit
   {
      class Output : public Abstract, private Ui::Output
      {
         Q_OBJECT

      public:
         Output(Persona* persona, const PatchParser::Marker& marker);

      private:
         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         DescriptionHighlighter* highlighter;
         int outputIndex;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditOutputH
