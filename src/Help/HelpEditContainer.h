#ifndef HelpEditContainerH
#define HelpEditContainerH

#include <QStackedWidget>

#include "HelpEditAbstract.h"
#include "HelpPatchStructure.h"

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
         using EditorMap = QMap<PatchStructure::Marker, Abstract*>;

      private:
         template <typename EditorType>
         void addEditor(const PatchStructure::Marker& marker);

         void componentSelected(PatchStructure::Marker marker, QVariant data) override;

      private:
         Persona* persona;
         EditorMap editorMap;
      };
   } // namespace Edit
} // namespace Help

#endif // NOT HelpEditContainerH
