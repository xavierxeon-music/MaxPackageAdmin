#ifndef HelpPageAbstractHPP
#define HelpPageAbstractHPP

#include "HelpPageAbstract.h"

template <typename DataType>
bool Help::Page::Abstract::copyIfChanged(DataType& target, const DataType& data)
{
   if (data == target)
      return false;

   target = data;
   Central::FunctionHub::callOnAllHubInstances(&Central::FunctionHub::setModified, true);

   return true;
}

#endif // NOT HelpPageAbstractHPP
