#ifndef HelpEditAbstractHPP
#define HelpEditAbstractHPP

#include "HelpEditAbstract.h"

template <typename DataType>
bool Help::Edit::Abstract::copyIfChanged(DataType& target, const DataType& data)
{
   if (data == target)
      return false;

   target = data;
   Central::FunctionHub::callOnAllHubInstances(&Central::FunctionHub::setModified, true);

   return true;
}

#endif // NOT HelpEditAbstractHPP
