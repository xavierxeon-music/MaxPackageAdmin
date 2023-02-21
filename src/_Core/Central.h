#ifndef CentralH
#define CentralH

#include "AbstractFunctionHub.h"

class Central
{
public:
   struct FunctionHub : public Abstract::FunctionHub<Central>
   {
      virtual void setPackagePath(QString packageDir);
      virtual void setModified(bool enabled);
   };

public:
   static QString getPackagePath();
   static QString getAuthor();
   static QString getPackageName();
};

#endif // NOT CentralH
