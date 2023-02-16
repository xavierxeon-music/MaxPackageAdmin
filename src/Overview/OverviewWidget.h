#ifndef OverviewWidgetH
#define OverviewWidgetH

#include "../PersonaWindow.h"

#include "PackageModel.h"

class OverviewWidget : public PersonaWindow
{
   Q_OBJECT
public:
   OverviewWidget(MainWidget* mainWidget);

signals:
   void signalUpdateTitle();

private slots:
   void slotOpenPackage();

private:
   Package::Model* packageModel;
};

#endif // NOT OverviewWidgetH
