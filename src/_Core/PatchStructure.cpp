#include "PatchStructure.h"

QString PatchStructure::typeName(const Type& type)
{
   switch (type)
   {
      case Type::Symbol:
         return "symbol";
      case Type::Float:
         return "float";
      case Type::Integer:
         return "int";
      case Type::Bang:
         return "bang";
      default:
         break;
   }

   return QString("???");
}

PatchStructure::Type PatchStructure::toType(const QString& name)
{
   if ("symbol" == name)
      return Type::Symbol;
   else if ("float" == name)
      return Type::Float;
   else if ("int" == name)
      return Type::Integer;
   else if ("bang" == name)
      return Type::Bang;

   return Type::Unkown;
}
