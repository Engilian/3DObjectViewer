#ifndef I_SCENE_3D_H
#define I_SCENE_3D_H

#include <QObject>

#include "object_viewer/canvas3d/canvas_3d.h"
#include "object_viewer/object3d/i_object_3d.h"

using Viewer3D = Canvas3D;

///
/// \brief Интерфейс сцены
///
class IScene3D: public QObject
{
    Q_OBJECT
protected:
    IScene3D();
public:
    virtual ~IScene3D();
public:

    ///
    /// \brief Область вывода
    /// \return область вывода
    ///
    virtual Viewer3D *viewPort() const = 0;

public:

    ///
    /// \brief Добавить объект на сцену
    /// \param obj объект
    ///
    virtual void addObject( Object3D obj ) = 0;

    ///
    /// \brief Удалить объект с сцены
    /// \param obj объект
    ///
    virtual void removeObject( Object3D obj ) = 0;

    ///
    /// \brief Список объектов сцены
    /// \return список объектов
    ///
    virtual QList<Object3D> objects() const = 0;

    ///
    /// \brief Наличие объекта на сцене
    /// \param obj объект
    /// \return если true то в наличии
    ///
    virtual bool contains( Object3D obj ) const = 0;

    ///
    /// \brief Очистить список объектов
    ///
    virtual void clearObjects() = 0;

signals:

    ///
    /// \brief Добавлен объект на сцену
    /// \param obj объект
    ///
    void AddedObject3d( Object3D obj );

    ///
    /// \brief Удален объект с сцены
    /// \param obj объект
    ///
    void RemovedObject3d( Object3D obj );

};

#endif // I_SCENE_3D_H
