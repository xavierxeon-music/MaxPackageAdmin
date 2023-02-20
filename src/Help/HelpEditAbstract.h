#ifndef HelpEditAbstractH
#define HelpEditAbstractH

#include <QWidget>

#include "HelpPatchStructure.h"
#include "HelpPersona.h"

namespace Help
{
   class Persona;

   namespace Edit
   {
      class Abstract : public QWidget
      {
         Q_OBJECT

      public:
         Abstract(Persona* persona, const PatchStructure::Marker& marker);
         virtual ~Abstract();

      protected:
         Persona* persona;
         const PatchStructure::Marker marker;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditAbstractH
