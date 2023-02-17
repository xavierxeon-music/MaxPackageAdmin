#include "Mac.h"
#import <Cocoa/Cocoa.h>

// https://stackoverflow.com/questions/55925862/how-can-i-set-my-os-x-application-theme-in-code

bool Mac::isInDarkTheme()
{
   auto appearance = [NSApp.effectiveAppearance bestMatchFromAppearancesWithNames:@[ NSAppearanceNameAqua, NSAppearanceNameDarkAqua ]];
   return [appearance isEqualToString:NSAppearanceNameDarkAqua];
}

void Mac::setToDarkTheme()
{
   [NSApp setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameDarkAqua]];
}

void Mac::setToLightTheme()
{
   [NSApp setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameAqua]];
}

void Mac::setToAutoTheme()
{
   [NSApp setAppearance:nil];
}
