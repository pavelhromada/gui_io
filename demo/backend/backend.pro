QT += core websockets
QT -= gui

CONFIG += c++11

TARGET = backend
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/controllers/logincontroller.cpp \
    src/controllers/menucontroller.cpp

HEADERS += \
    src/controllers/logincontroller.h \
    src/controllers/menucontroller.h

unix:!macx: LIBS += -L$$PWD/guiserver_lib/ -lGuiIOServer

INCLUDEPATH += $$PWD/guiserver_lib
DEPENDPATH += $$PWD/guiserver_lib

unix:!macx: PRE_TARGETDEPS += $$PWD/guiserver_lib/libGuiIOServer.a
