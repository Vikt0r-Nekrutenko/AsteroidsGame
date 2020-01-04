TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += _WINDOWS

SOURCES += \
    GlobalSettings.cpp \
    SpritesHolder.cpp \
    game.cpp

HEADERS += \
    Framework.h \
    GlobalSettings.h \
    SpritesHolder.h

win32: LIBS += -L$$PWD/release/ -lFrameworkRelease_x64

INCLUDEPATH += $$PWD/release
DEPENDPATH += $$PWD/release
