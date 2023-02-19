#ifndef HelpComponentEditorH
#define HelpComponentEditorH

#include <QWidget>

namespace Help
{
   class Persona;

   class ComponentEditor : public QWidget
   {
      Q_OBJECT

   public:
      ComponentEditor(Persona* persona);

   private:
      Persona* persona;
   };
} // namespace Help

#endif // NOT HelpComponentEditorH
