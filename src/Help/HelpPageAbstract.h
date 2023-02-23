#ifndef HelpPageAbstractH
#define HelpPageAbstractH

#include <QWidget>

#include <Central.h>

#include "HelpPatchParser.h"
#include "HelpPersona.h"

namespace Help
{
   class Persona;

   namespace Page
   {
      class Abstract : public QWidget,
                       protected Persona::FunctionHub,
                       private Central::FunctionHub
      {
         Q_OBJECT

      public:
         Abstract(Persona* persona, const PatchParser::Marker& marker);
         virtual ~Abstract();

      protected:
         virtual void componentSelected(PatchParser::Marker marker, QVariant data) override = 0;

         template <typename DataType>
         bool copyIfChanged(DataType& target, const DataType& data);

      protected:
         Persona* persona;
         const PatchParser::Marker editMarker;
      };
   } // namespace Edit
} // namespace Help

#ifndef HelpPageAbstractHPP
#include "HelpPageAbstract.hpp"
#endif // NOT HelpPageAbstractHPP

#endif // NOT HelpPageAbstractH
