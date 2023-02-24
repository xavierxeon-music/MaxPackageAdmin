#include "HelpArgumentView.h"

#include <QComboBox>

static constexpr int TypeRole = Qt::UserRole + 1;

// view

Help::ArgumentView::ArgumentView(QWidget* parent)
   : QTreeView(parent)
   , argumentList()
   , argumentModel(nullptr)
   , nameEditable(false)
{
   setRootIsDecorated(false);

   argumentModel = new QStandardItemModel(this);
   connect(argumentModel, &QStandardItemModel::itemChanged, this, &ArgumentView::slotItemChanged);
   setModel(argumentModel);

   setItemDelegateForColumn(2, new TypeDelegate(this));
}

void Help::ArgumentView::allowNameEdit(bool allow)
{
   nameEditable = allow;
}

void Help::ArgumentView::clearMonitors()
{
   argumentList.clear();
   argumentModel->clear();
   argumentModel->setHorizontalHeaderLabels({"O", "Name", "Type"});
}

void Help::ArgumentView::monitor(PatchStructure::Argument* argument)
{
   QStandardItem* optionalItem = new QStandardItem();
   optionalItem->setCheckable(true);
   optionalItem->setCheckState(argument->optional ? Qt::Checked : Qt::Unchecked);

   QStandardItem* nameItem = new QStandardItem(argument->name);
   nameItem->setEditable(nameEditable);

   QStandardItem* typeItem = new QStandardItem(PatchStructure::typeName(argument->type));
   typeItem->setData(QVariant::fromValue(argument->type), TypeRole);

   argumentModel->appendRow({optionalItem, nameItem, typeItem});
   argumentList.append(argument);

   resizeColumnToContents(0);
   resizeColumnToContents(1);
}

void Help::ArgumentView::slotItemChanged(QStandardItem* item)
{
   qDebug() << __FUNCTION__ << item->column() << item->text() << item->data(TypeRole);
}

// delegate

Help::TypeDelegate::TypeDelegate(ArgumentView* view)
   : QStyledItemDelegate(view)
   , view(view)
   , typeModel(nullptr)
{
   static const QList<PatchStructure::Type> typeList = {PatchStructure::Type::Symbol,
                                                        PatchStructure::Type::Float,
                                                        PatchStructure::Type::Integer,
                                                        PatchStructure::Type::Bang,
                                                        PatchStructure::Type::List,
                                                        PatchStructure::Type::Signal};

   typeModel = new QStandardItemModel(this);
   for (const PatchStructure::Type& type : typeList)
   {
      QStandardItem* nameItem = new QStandardItem(PatchStructure::typeName(type));
      nameItem->setEditable(false);
      typeModel->appendRow(nameItem);
   }
}

QWidget* Help::TypeDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   Q_UNUSED(option)
   Q_UNUSED(index)

   QComboBox* comboBox = new QComboBox(parent);
   comboBox->setModel(typeModel);
   return comboBox;
}

void Help::TypeDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
   QComboBox* comboBox = qobject_cast<QComboBox*>(editor);

   const PatchStructure::Type type = view->argumentList.at(index.row())->type;
   const int typeIndex = comboBox->findText(PatchStructure::typeName(type));
   comboBox->setCurrentIndex(typeIndex);
}

void Help::TypeDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
   QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
   const QString typeText = comboBox->currentText();

   model->setData(index, comboBox->currentText(), Qt::DisplayRole);
}

void Help::TypeDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   Q_UNUSED(index)

   editor->setGeometry(option.rect);
}
