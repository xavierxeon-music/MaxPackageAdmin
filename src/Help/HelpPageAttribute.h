#ifndef HelpPageAttributeH
#define HelpPageAttributeH

#include "HelpPageAbstract.h"
#include "ui_HelpPageAttribute.h"

#include "HelpDescriptionHighlighter.h"

namespace Help
{
   namespace Page
   {
      class Attribute : public Abstract, private Ui::Attribute
      {
         Q_OBJECT

      public:
         Attribute(Persona* persona, const PatchParser::Marker& marker);

      private:
         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         DescriptionHighlighter* highlighter;
         QString attributeName;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpPageAttributeH
