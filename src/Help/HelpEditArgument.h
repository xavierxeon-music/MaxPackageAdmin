#ifndef HelpEditArgumentH
#define HelpEditArgumentH

#include "HelpEditAbstract.h"
#include "ui_HelpEditArgument.h"

namespace Help
{
   namespace Edit
   {
      class Argument : public Abstract, private Ui::Argument
      {
         Q_OBJECT

      public:
         Argument(Persona* persona, const PatchStructure::Marker& marker);

      private:
         void componentSelected(PatchStructure::Marker marker, QVariant data) override;

      private:
         int argumentIndex;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditArgumentH
