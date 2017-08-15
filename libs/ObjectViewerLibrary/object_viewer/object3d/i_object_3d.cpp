#include "i_object_3d.h"

IObject3D::IObject3D(): ITransformational()
{
    _globalTransform.setToIdentity();
    _scale = 1.0f;
}

IObject3D::~IObject3D()
{

//    ITransformational::~ITransformational();
}

QString IObject3D::name() const
{
    return __objectName;
}

void IObject3D::setName(const QString name)
{
    __objectName = name;
}

void IObject3D::rotate(const QQuaternion &q)
{
    _rotate = q * _rotate;
}

void IObject3D::translate(const QVector3D &t)
{
    _translate += t;
}

void IObject3D::scale(const float scale)
{
    _scale *= scale;
}

void IObject3D::setGlobalTransform(const QMatrix4x4 &m)
{
    _globalTransform = m;
}

QMatrix4x4 IObject3D::createModelMatrix() const
{
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate( _translate );
    modelMatrix.rotate( _rotate );
    modelMatrix.scale( _scale );

    modelMatrix = _globalTransform * modelMatrix;

    return modelMatrix;
}

QQuaternion IObject3D::currentRorate() const
{
    return _rotate;
}

QVector3D IObject3D::currentTranslate() const
{
    return _translate;
}
