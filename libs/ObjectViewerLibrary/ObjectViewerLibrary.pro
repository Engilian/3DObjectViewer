QT       += opengl
QT       -= gui

TARGET = obj_viewer_3d
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

SOURCES += object_viewer_info.cpp \
    object_viewer/object3d/i_object_3d.cpp \
    object_viewer/object3d/shapes/other/simple_object_3d.cpp \
    object_viewer/object3d/shapes/cube/cube_3d.cpp \
    object_viewer/object3d/shapes/cube/example_cube_3d.cpp \
    object_viewer/object3d/group/group_3d.cpp \
    object_viewer/canvas3d/canvas_3d.cpp \
    object_viewer/object3d/camera/camera_3d.cpp \
    object_viewer/object3d/skybox/i_skybox.cpp \
    object_viewer/object3d/skybox/skybox_one_cube_texture.cpp \
    object_viewer/object3d/skybox/skybox_six_textutes.cpp \
    object_viewer/object3d/object_loader/i_object_loader.cpp \
    object_viewer/object3d/shapes/triangle_object/triangleobject3d.cpp \
    object_viewer/object3d/object_loader/object_loader_triangle_object3d.cpp \
    object_viewer/object3d/object_loader/object_loader_simple_object3d.cpp \
    object_viewer/scene3d/i_scene_3d.cpp \
    object_viewer/scene3d/simple_scene_3d.cpp

HEADERS += object_viewer_info.h \
    object_viewer/object3d/i_object_3d.h \
    object_viewer/object3d/shapes/other/simple_object_3d.h \
    object_viewer/object3d/shapes/cube/cube_3d.h \
    object_viewer/object3d/shapes/cube/example_cube_3d.h \
    object_viewer/object3d/i_transformational.h \
    object_viewer/object3d/group/group_3d.h \
    object_viewer/canvas3d/canvas_3d.h \
    object_viewer/object3d/camera/camera_3d.h \
    object_viewer/object3d/skybox/i_skybox.h \
    object_viewer/object3d/skybox/skybox_one_cube_texture.h \
    object_viewer/object3d/skybox/skybox_six_textutes.h \
    object_viewer/object3d/object_loader/i_object_loader.h \
    object_viewer/object3d/shapes/triangle_object/triangleobject3d.h \
    object_viewer/object3d/object_loader/object_loader_triangle_object3d.h \
    object_viewer/object3d/object_loader/object_loader.h \
    object_viewer/object3d/object_loader/object_loader_simple_object3d.h \
    object_viewer/scene3d/i_scene_3d.h \
    object_viewer/scene3d/simple_scene_3d.h \
    object_viewer/scene3d/scene_3d.h

RESOURCES += \
    res/shaders/shaders.qrc \
    res/textures/textures.qrc \
    res/models/models.qrc
