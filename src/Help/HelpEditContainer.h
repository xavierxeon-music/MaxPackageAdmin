#ifndef HelpEditContainerH
#define HelpEditContainerH

#include <QStackedWidget>

#include "HelpEditAbstract.h"
#include "HelpPatchParser.h"

namespace Help
{
   class Persona;

   namespace Edit
   {
      class Container : public QStackedWidget,
                        private Persona::FunctionHub
      {
         Q_OBJECT

      public:
         Container(Persona* persona);

      private:
         using EditorMap = QMap<PatchParser::Marker, Abstract*>;

      private:
         template <typename EditorType>
         void addEditor(const PatchParser::Marker& marker);

         void componentSelected(PatchParser::Marker marker, QVariant data) override;

      private:
         Persona* persona;
         EditorMap editorMap;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditContainerH
