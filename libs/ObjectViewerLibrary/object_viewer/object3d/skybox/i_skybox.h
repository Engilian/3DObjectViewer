#ifndef I_SKYBOX_H
#define I_SKYBOX_H

#include "object_viewer/object3d/shapes/other/simple_object_3d_v1.h"

///
/// \brief Интерфейс skybox
///
class ISkyBox: public ITransformational
{
protected:
    ISkyBox();
public:
    virtual ~ISkyBox();
public:
    void rotate( const QQuaternion &q );
    void translate( const QVector3D &t );
    void scale( const float scale );
    void setGlobalTransform( const QMatrix4x4 &m );

public:
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions) = 0;
};

#endif // I_SKYBOX_H
