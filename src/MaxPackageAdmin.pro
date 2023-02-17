TARGET = MaxPackageAdmin
TEMPLATE = app

QT += widgets xml svg
CONFIG += c++17

DESTDIR = ../bin

include(Main/Main.pri)
include(_Core/_Core.pri)

include(Overview/Overview.pri)
include(Help/Help.pri)

HEADERS += \
   MainWidget.h

SOURCES += \
   MainWidget.cpp




