#ifndef CentralH
#define CentralH

#include "AbstractFunctionHub.h"

class Central
{
public:
   struct FunctionHub : public Abstract::FunctionHub<Central>
   {
      virtual void setPackagePath(QString packageDir);
   };

public:
   static QString getPackagePath();
};

#endif // NOT CentralH
