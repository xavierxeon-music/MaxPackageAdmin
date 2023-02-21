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
      class Abstract : public QWidget,
                       protected Persona::FunctionHub
      {
         Q_OBJECT

      public:
         Abstract(Persona* persona, const PatchStructure::Marker& marker);
         virtual ~Abstract();

      protected:
         virtual void componentSelected(PatchStructure::Marker marker, QVariant data) = 0;
         PatchStructure* structureRef();

      private:
         void patchSelected(QString patchPath, QString key) override final;

      protected:
         Persona* persona;
         QString key;
         const PatchStructure::Marker marker;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditAbstractH
