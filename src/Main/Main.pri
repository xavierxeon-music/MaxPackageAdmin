macx {
    ICON = $$PWD/resources/MPA.icns
    CONFIG(release, debug|release): DESTDIR = ~/Applications

    HEADERS += $$PWD/MacTheme.h
    OBJECTIVE_SOURCES += $$PWD/MacTheme.mm
}

windows {
    RC_ICONS = $$PWD/resources/MPA.ico
}

HEADERS += \
    $$PWD/SpacerToolBar.h \
    $$PWD/TabToolBar.h

SOURCES += \    
    $$PWD/SpacerToolBar.cpp \
    $$PWD/TabToolBar.cpp


RESOURCES += \
   $$PWD/resources/resources.qrc
