#include "simple_scene_3d.h"

SimpleScene3D::SimpleScene3D(Viewer3D *viewPort)
{
    __viewPort = viewPort;
}

SimpleScene3D::~SimpleScene3D()
{
    clearObjects ();
}

Viewer3D *SimpleScene3D::viewPort() const
{
    return __viewPort;
}

void SimpleScene3D::addObject(Object3D obj)
{
    if  ( !__objects.contains ( obj ) ) {

        __objects << obj;

        if ( __viewPort ) {
            __viewPort->objects ()->append ( obj );
        }

        emit AddedObject3d ( obj );
    }
}

void SimpleScene3D::removeObject(Object3D obj)
{
    __objects.removeOne ( obj );
    __viewPort->objects ()->removeOne ( obj );

    emit RemovedObject3d ( obj );
}

QList<Object3D> SimpleScene3D::objects() const
{
    return __objects;
}

bool SimpleScene3D::contains(Object3D obj) const
{
    return __objects.contains ( obj );
}

void SimpleScene3D::clearObjects()
{
    for ( Object3D &obj: __objects ) {

        if ( __viewPort ) {

            __viewPort->objects ()->removeOne ( obj );
            emit RemovedObject3d ( obj );
        }
    }

    __objects.clear ();
}
