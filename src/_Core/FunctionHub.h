#ifndef FunctionHubH
#define FunctionHubH

#include <QList>

template <typename WhatEver> // the typename is not used
class FunctionHub
{
public:
   inline FunctionHub();
   inline ~FunctionHub();

private:
   static QList<FunctionHub*> instanceList;
};

#ifndef FunctionHubHPP
#include "FunctionHub.hpp"
#endif // NOT FunctionHubHPP

#endif // NOT FunctionHubH
