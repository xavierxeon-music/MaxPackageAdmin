#ifndef AbstractPersonaH
#define AbstractPersonaH

#include <QWidget>

#include <QSplitter>
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
      static void callOnAllInstances(void (Persona::*functionPointer)());
      virtual void laodState();
      virtual void saveState();

   protected:
      QToolBar* getToolBar();
      void addWidget(QWidget* widget, const QString& title);

   protected:
      MainWidget* mainWidget;

   private:
      static QList<Persona*> personaList;
      const QString name;
      QToolBar* toolBar;
      QSplitter* splitter;
   };
} // namespace Abstract

#endif // NOT AbstractPersonaH
