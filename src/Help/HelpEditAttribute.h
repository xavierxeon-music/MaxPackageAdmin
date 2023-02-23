#ifndef HelpEditAttributeH
#define HelpEditAttributeH

#include "HelpEditAbstract.h"
#include "ui_HelpEditAttribute.h"

namespace Help
{
   namespace Edit
   {
      class Attribute : public Abstract, private Ui::Attribute
      {
         Q_OBJECT

      public:
         Attribute(Persona* persona, const PatchParser::Marker& marker);

      private:
         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         QString attributeName;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditAttributeH
