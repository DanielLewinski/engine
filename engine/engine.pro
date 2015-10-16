TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += source/main.cpp \
    source/window.cpp \
    source/exceptions.cpp \
    source/gameobject.cpp \
    source/button.cpp \
    source/font.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    source/window.h \
    source/exceptions.h \
    source/gameobject.h \
    source/button.h \
    source/font.h

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf
