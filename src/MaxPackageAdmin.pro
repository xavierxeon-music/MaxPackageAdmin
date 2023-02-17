TARGET = MaxPackageAdmin
TEMPLATE = app

QT += widgets xml svg
CONFIG += c++17

DESTDIR = ../bin

mac{
   ICON = resources/MPA.icns
   CONFIG(release, debug|release): DESTDIR = ~/Applications
}

include(_Core/_Core.pri)
include(Overview/Overview.pri)
include(Help/Help.pri)

HEADERS += \
   MainWidget.h

SOURCES += \
   MainWidget.cpp

RESOURCES += \
   resources/resources.qrc



