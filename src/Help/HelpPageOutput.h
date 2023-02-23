#ifndef HelpPageOutputH
#define HelpPageOutputH

#include "HelpPageAbstract.h"
#include "ui_HelpPageOutput.h"

#include "HelpDescriptionHighlighter.h"

namespace Help
{
   namespace Page
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

#endif // NOT HelpPageOutputH
