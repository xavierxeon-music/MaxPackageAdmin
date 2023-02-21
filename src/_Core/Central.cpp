#include "Central.h"

#include <Settings.h>

void Central::FunctionHub::setPackagePath(QString packageDir)
{
   // do nothing
   Q_UNUSED(packageDir);
}

void Central::FunctionHub::setModified(bool enabled)
{
   // do nothing
   Q_UNUSED(enabled);
}

QString Central::getPackagePath()
{
   Settings settings;
   const QString packagePath = settings.string("LastPackage");

   return packagePath;
}

QString Central::getAuthor()
{
   return "Ralf Waspe";
}

QString Central::getPackageName()
{
   return "WaMaxPackage";
}
