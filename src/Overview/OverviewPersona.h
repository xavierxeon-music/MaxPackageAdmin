#ifndef OverviewPersonaH
#define OverviewPersonaH

#include <Persona.h>

#include "PackageModel.h"

class OverviewPersona : public Persona
{
   Q_OBJECT
public:
   OverviewPersona(MainWidget* mainWidget);

signals:
   void signalUpdateTitle();

private slots:
   void slotOpenPackage();

private:
   Package::Model* packageModel;
};

#endif // NOT OverviewPersonaH
