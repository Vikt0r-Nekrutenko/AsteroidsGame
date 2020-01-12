TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += _WINDOWS

SOURCES += \
    AsteroidsData.cpp \
    BulletsData.cpp \
    Destructible.cpp \
    GlobalSettings.cpp \
    Improvable.cpp \
    ImprovementsData.cpp \
    Map.cpp \
    PlayerData.cpp \
    SpaceObjectsData.cpp \
    SpritesDataHolder.cpp \
    Vector2d.cpp \
    game.cpp

HEADERS += \
    AsteroidsData.h \
    BulletsData.h \
    Destructible.h \
    Framework.h \
    GlobalSettings.h \
    Improvable.h \
    ImprovementsData.h \
    Map.h \
    PlayerData.h \
    SpaceObjectsData.h \
    SpritesDataHolder.h \
    Vector2d.h \
    game.h

win32: LIBS += -L$$PWD/release/ -lFrameworkRelease_x64

INCLUDEPATH += $$PWD/release
DEPENDPATH += $$PWD/release
