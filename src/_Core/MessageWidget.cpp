#include "MessageWidget.h"

MessageWidget::MessageWidget(QWidget* parent)
   : QTreeWidget(parent)
{
}

void MessageWidget::info(const QString& message)
{
   qInfo() << message;
}

void MessageWidget::warning(const QString& message)
{
   qWarning() << message;
}

void MessageWidget::error(const QString& message)
{
   qWarning() << message;
}
