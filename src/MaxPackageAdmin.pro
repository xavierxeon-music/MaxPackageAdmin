TARGET = MaxPackageAdmin
TEMPLATE = app

QT += widgets xml svg
CONFIG += c++17

DESTDIR = ../bin

mac{
   ICON = resources/MPA.icns
   CONFIG(release, debug|release): DESTDIR = ~/Applications
}

include(Overview/Overview.pri)
include(Help/Help.pri)

HEADERS += \
   MainWidget.h \
   PersonaWindow.h \
   Settings.h

SOURCES += \
   MainWidget.cpp \
   PersonaWindow.cpp \
   Settings.cpp

RESOURCES += \
   resources/resources.qrc



