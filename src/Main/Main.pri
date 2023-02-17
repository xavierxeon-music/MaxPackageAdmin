macx {
    ICON = $$PWD/resources/MPA.icns
    CONFIG(release, debug|release): DESTDIR = ~/Applications

    HEADERS += $$PWD/Mac.h
    OBJECTIVE_SOURCES += $$PWD/Mac.mm
}

HEADERS += \
    $$PWD/MessageBar.h \
    $$PWD/SpacerToolBar.h \
    $$PWD/TabToolBar.h

SOURCES += \
    $$PWD/MessageBar.cpp \
    $$PWD/SpacerToolBar.cpp \
    $$PWD/TabToolBar.cpp


RESOURCES += \
   $$PWD/resources/resources.qrc
