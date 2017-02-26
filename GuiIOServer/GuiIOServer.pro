QT       += websockets
QT       -= gui

TARGET = GuiIOServer
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += src/guiioserver.cpp \
    src/guiio.cpp \
    src/guiio_p.cpp

HEADERS += include/guiioserver.h \
    include/guiio.h \
    src/guiio_p.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
