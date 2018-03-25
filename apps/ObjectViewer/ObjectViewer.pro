QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = ObjectViewer
TEMPLATE    = app
CONFIG      += c++11
DESTDIR     = ../../bin

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000


SOURCES += \
        main.cpp \
        main_window.cpp \
    listObject3d/list_object3d.cpp

HEADERS += \
        main_window.h \
    listObject3d/list_object3d.h

FORMS += \
        main_window.ui

RESOURCES += \
    ../../libs/ObjectViewerLibrary/res/shaders/shaders.qrc

include(viewer.pri)
