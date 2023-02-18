#ifndef HelpPersonaH
#define HelpPersonaH

#include <AbstractPersona.h>

namespace Help
{
   class Persona : public Abstract::Persona
   {
      Q_OBJECT
   public:
      Persona(MainWidget* mainWidget);
   };
} // namespace Help

#endif // NOT HelpPersonaH
