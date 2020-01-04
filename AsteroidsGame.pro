TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += _WINDOWS

SOURCES += \
    GlobalSettings.cpp \
    SpritesDataHolder.cpp \
    Vector2d.cpp \
    game.cpp

HEADERS += \
    Framework.h \
    GlobalSettings.h \
    SpritesDataHolder.h \
    Vector2d.h

win32: LIBS += -L$$PWD/release/ -lFrameworkRelease_x64

INCLUDEPATH += $$PWD/release
DEPENDPATH += $$PWD/release
