#ifndef HelpPageMessageH
#define HelpPageMessageH

#include "HelpPageAbstract.h"
#include "ui_HelpPageMessage.h"

#include "HelpDescriptionHighlighter.h"

namespace Help
{
   namespace Page
   {
      class Message : public Abstract, private Ui::Message
      {
         Q_OBJECT

      public:
         Message(Persona* persona, const PatchParser::Marker& marker);

      private:
         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         DescriptionHighlighter* highlighter;
         QString messageName;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpPageMessageH
