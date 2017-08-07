#ifndef SIMPLE_SCENE_3D_H
#define SIMPLE_SCENE_3D_H

#include "i_scene_3d.h"

///
/// \brief Простая сцена
///
class SimpleScene3D : public IScene3D
{
    Q_OBJECT
public:
    SimpleScene3D( Viewer3D *viewPort );
    ~SimpleScene3D();
public:

    Viewer3D *viewPort() const;
public:

    void addObject( Object3D obj );
    void removeObject( Object3D obj );
    QList<Object3D> objects() const;
    bool contains( Object3D obj ) const;
    void clearObjects();

private:

    ///
    /// \brief Область вывода
    ///
    Viewer3D        *__viewPort;

    ///
    /// \brief Список объектов для вывода
    ///
    QList<Object3D> __objects;

};

#endif // SIMPLE_SCENE_3D_H
