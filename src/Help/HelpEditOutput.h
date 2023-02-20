#ifndef HelpEditOutputH
#define HelpEditOutputH

#include "HelpEditAbstract.h"
#include "ui_HelpEditOutput.h"

namespace Help
{
   namespace Edit
   {
      class Output : public Abstract, private Ui::Output
      {
         Q_OBJECT

      public:
         Output(Persona* persona, const PatchStructure::Marker& marker);
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditOutputH
