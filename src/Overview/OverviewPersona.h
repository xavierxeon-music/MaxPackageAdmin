#ifndef OverviewPersonaH
#define OverviewPersonaH

#include <Persona.h>

#include "PackageModel.h"
#include "PatchModel.h"

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
   Patch::Model* patchModel;
};

#endif // NOT OverviewPersonaH
