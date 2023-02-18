#include "OverviewPatchModel.h"

Overview::PatchModel::PatchModel(QObject* parent)
   : JSON::Model(parent)
   , Persona::FunctionHub()
{
}

void Overview::PatchModel::patchSelected(QString patchPath)
{
   JSON::Model::readFile(patchPath);
}
