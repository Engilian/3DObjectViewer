#include "group_3d.h"

Group3D::Group3D(const QString &name)
{
    setName( name );
}

Group3D::~Group3D()
{

//    IObject3D::~IObject3D();
}

void Group3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    QMatrix4x4 modelMatrix = createModelMatrix();

    for ( const Object3D &obj: __objects ) {
        obj.get()->setGlobalTransform( modelMatrix );
        obj.get()->draw( program, functions );
    }
}

void Group3D::addObject(const Object3D obj)
{
    __objects << obj;
}

void Group3D::removeObject(const Object3D obj)
{
    __objects.removeOne( obj );
}
