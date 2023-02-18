#ifndef AbstractItemTreeViewH
#define AbstractItemTreeViewH

#include <QTreeView>

#include <QStandardItemModel>

namespace Abstract
{
   class ItemTreeView : public QTreeView
   {
      Q_OBJECT
   public:
      ItemTreeView(QWidget* parent, QStandardItemModel* model);

   public:
      template <typename ItemModel>
      ItemModel* getModel();

   protected:
      virtual void clicked(QStandardItem* item);
      virtual void doubleClicked(QStandardItem* item);

   private slots:
      void slotClicked(const QModelIndex& index);
      void slotDoubleClicked(const QModelIndex& index);
      void slotResizeAllColumns();

   private:
      QStandardItemModel* model;
   };

} // namespace Abstract

#ifndef AbstractItemTreeViewHPP
#include "AbstractItemTreeView.hpp"
#endif // NOT AbstractItemTreeViewHPP

#endif // NOT AbstractItemTreeViewH
