#ifndef TabToolBarH
#define TabToolBarH

#include <QToolBar>

#include <QButtonGroup>

class MainWidget;

class TabToolBar : public QToolBar
{
   Q_OBJECT
public:
   TabToolBar(MainWidget* mainWidget);

public slots:
   void slotChangeTab(int index);

public:
   void addTab(const int& index, const QString& name);

private:
   MainWidget* mainWidget;
   QButtonGroup* buttonGroup;
};

#endif // NOT TabToolBarH
