#include "HelpFileModel.h"

Help::FileModel::FileModel(QObject* parent)
   : QStandardItemModel(parent)
{
}

void Help::FileModel::patchSelected(QString patchPath, QString helpPath)
{
   Q_UNUSED(patchPath)
   clear();
}
