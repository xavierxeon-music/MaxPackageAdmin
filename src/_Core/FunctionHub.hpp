#ifndef FunctionHubHPP
#define FunctionHubHPP

#include "FunctionHub.h"

template <typename WhatEver>
QList<FunctionHub<WhatEver>*> FunctionHub<WhatEver>::instanceList;

template <typename WhatEver>
FunctionHub<WhatEver>::FunctionHub()
{
   instanceList.append(this);
}

template <typename WhatEver>
FunctionHub<WhatEver>::~FunctionHub()
{
   instanceList.removeAll(this);
}

#endif // NOT FunctionHubHPP
