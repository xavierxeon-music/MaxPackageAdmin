#include "PatchStructure.h"

QString PatchStructure::typeName(const Type& type)
{
   switch (type)
   {
      case Symbol:
         return "symbol";
      case Float:
         return "float";
      case Integer:
         return "int";
      default:
         break;
   }

   return QString("???");
}
