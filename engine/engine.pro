TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += source/main.cpp \
    source/window.cpp \
    source/exceptions.cpp \
    source/gameobject.cpp \
    source/button.cpp \
    source/font.cpp \
    source/sounds.cpp \
    source/timer.cpp \
    source/uiobject.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    source/window.h \
    source/exceptions.h \
    source/gameobject.h \
    source/button.h \
    source/font.h \
    source/sounds.h \
    source/timer.h \
    source/uiobject.h

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
