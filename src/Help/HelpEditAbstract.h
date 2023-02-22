#ifndef HelpEditAbstractH
#define HelpEditAbstractH

#include <QWidget>

#include <Central.h>

#include "HelpPatchStructure.h"
#include "HelpPersona.h"

namespace Help
{
   class Persona;

   namespace Edit
   {
      class Abstract : public QWidget,
                       protected Persona::FunctionHub,
                       private Central::FunctionHub
      {
         Q_OBJECT

      public:
         Abstract(Persona* persona, const PatchStructure::Marker& marker);
         virtual ~Abstract();

      protected:
         virtual void componentSelected(PatchStructure::Marker marker, QVariant data) override = 0;
         const PatchStructure& structure() const;
         PatchStructure& structureRef();

         template <typename DataType>
         bool copyIfChanged(DataType& target, const DataType& data);

      private:
         void patchSelected(QString patchPath, QString key) override final;

      protected:
         Persona* persona;
         QString key;
         const PatchStructure::Marker marker;
      };
   } // namespace Edit
} // namespace Help

#ifndef HelpEditAbstractHPP
#include "HelpEditAbstract.hpp"
#endif // NOT HelpEditAbstractHPP

#endif // NOT HelpEditAbstractH
