#include "TabToolBar.h"

#include <QPushButton>

#include "../MainWidget.h"

TabToolBar::TabToolBar(MainWidget* mainWidget)
   : QToolBar(mainWidget)
   , mainWidget(mainWidget)
   , buttonGroup(nullptr)
{
   buttonGroup = new QButtonGroup(this);
   connect(buttonGroup, &QButtonGroup::idClicked, this, &TabToolBar::slotChangeTab);

   setMovable(false);
}

void TabToolBar::addTab(const int& index, const QString& name)
{
   QPushButton* button = new QPushButton(name, this);
   button->setFixedSize(48, 48);
   button->setCheckable(true);
   addWidget(button);

   buttonGroup->addButton(button, index);
}

void TabToolBar::slotChangeTab(int index)
{
   buttonGroup->button(index)->setChecked(true);

   mainWidget->centralStackWidget->setCurrentIndex(index);

   using ToolBarMap = MainWidget::ToolBarMap;
   ToolBarMap toolBarMap = mainWidget->toolBarMap;

   for (ToolBarMap::Iterator it = toolBarMap.begin(); it != toolBarMap.end(); it++)
   {
      QToolBar* toolBar = it.value();
      toolBar->setVisible(it.key() == index);
   }
}
