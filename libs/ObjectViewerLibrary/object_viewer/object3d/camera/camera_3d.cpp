#include "camera_3d.h"

Camera3D::Camera3D(QString name)
{
//    translate( QVector3D( 0.0f, 0.0f, -5.0f ) );
    _globalTransform.setToIdentity();
    setName( name );
}

Camera3D::~Camera3D()
{

}

void Camera3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    (void)functions;
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.rotate( _rotate );
    viewMatrix.translate( _translate );
    viewMatrix.scale( _scale );

    viewMatrix = viewMatrix * _globalTransform.inverted();
    program->setUniformValue("u_viewMatrix", viewMatrix);
}

void Camera3D::resetRotation()
{
    _rotate = QQuaternion();
}

void Camera3D::move(QVector3D &vector)
{
    translate( _rotate.inverted().rotatedVector( vector ) );
}
