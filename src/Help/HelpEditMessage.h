#ifndef HelpEditMessageH
#define HelpEditMessageH

#include "HelpEditAbstract.h"
#include "ui_HelpEditMessage.h"

namespace Help
{
   namespace Edit
   {
      class Message : public Abstract, private Ui::Message
      {
         Q_OBJECT

      public:
         Message(Persona* persona, const PatchParser::Marker& marker);

      private:
         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         QString messageName;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditMessageH
