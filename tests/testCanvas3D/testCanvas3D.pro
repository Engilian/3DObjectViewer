#-------------------------------------------------
#
# Project created by QtCreator 2017-08-05T22:25:26
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testCanvas3D
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        main_window.cpp \
    load_object_runnuble.cpp

HEADERS  += main_window.h \
    load_object_runnuble.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/ObjectViewerLibrary/release/ -lobj_viewer_3d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/ObjectViewerLibrary/debug/ -lobj_viewer_3d
else:unix: LIBS += -L$$OUT_PWD/../../libs/ObjectViewerLibrary/ -lobj_viewer_3d

INCLUDEPATH += $$PWD/../../libs/ObjectViewerLibrary
DEPENDPATH += $$PWD/../../libs/ObjectViewerLibrary

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/ObjectViewerLibrary/release/libobj_viewer_3d.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/ObjectViewerLibrary/debug/libobj_viewer_3d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/ObjectViewerLibrary/release/obj_viewer_3d.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/ObjectViewerLibrary/debug/obj_viewer_3d.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/ObjectViewerLibrary/libobj_viewer_3d.a


win32-msvc* {
LIBS += opengl32.lib
}

win32-g* {
LIBS += -lopengl32
}

RESOURCES += \
    ../../libs/ObjectViewerLibrary/res/shaders/shaders.qrc \
    ../../libs/ObjectViewerLibrary/res/textures/textures.qrc \
    ../../libs/ObjectViewerLibrary/res/models/models.qrc
