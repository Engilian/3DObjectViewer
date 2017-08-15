#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "../i_object_3d.h"

class Camera3D : public IObject3D
{
public:
    Camera3D( QString name = "mainCamera" );
    ~Camera3D();
public:

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions );

    void resetRotation();

public:

    void move( QVector3D &vector );

//    void roate( QVector3D &vector );
};

#endif // CAMERA_3D_H
