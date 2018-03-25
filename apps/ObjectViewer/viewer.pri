win32-msvc* {
LIBS += opengl32.lib
}

win32-g* {
LIBS += -lopengl32
}

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
