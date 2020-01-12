TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += _WINDOWS

SOURCES += \
    AsteroidsData.cpp \
    Destructible.cpp \
    GlobalSettings.cpp \
    Map.cpp \
    SpaceObjectsData.cpp \
    SpritesDataHolder.cpp \
    Vector2d.cpp \
    game.cpp

HEADERS += \
    AsteroidsData.h \
    Destructible.h \
    Framework.h \
    GlobalSettings.h \
    Map.h \
    SpaceObjectsData.h \
    SpritesDataHolder.h \
    Vector2d.h \
    game.h

win32: LIBS += -L$$PWD/release/ -lFrameworkRelease_x64

INCLUDEPATH += $$PWD/release
DEPENDPATH += $$PWD/release
