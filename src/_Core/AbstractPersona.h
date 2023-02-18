#ifndef AbstractPersonaH
#define AbstractPersonaH

#include <QWidget>

#include <QStatusBar>
#include <QToolBar>

class MainWidget;

namespace Abstract
{
   class Persona : public QWidget
   {
      Q_OBJECT
   public:
      Persona(MainWidget* mainWidget, const QString& name);
      virtual ~Persona();

   public:
      static void initAll();

   protected:
      virtual void init();
      QToolBar* getToolBar();

   protected:
      MainWidget* mainWidget;

   private:
      static QList<Persona*> personaList;
      const QString& name;
      QToolBar* toolBar;
   };
} // namespace Abstract

#endif // NOT AbstractPersonaH
