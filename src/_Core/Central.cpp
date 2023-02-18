#include "Central.h"

#include <Settings.h>

void Central::FunctionHub::setPackagePath(QString packageDir)
{
   // do nothing
   Q_UNUSED(packageDir);
}

QString Central::getPackagePath()
{
   Settings settings;
   const QString packagePath = settings.string("LastPackage");

   return packagePath;
}
