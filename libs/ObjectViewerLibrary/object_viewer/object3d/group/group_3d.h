#ifndef GROUP_3D_H
#define GROUP_3D_H

#include "../i_object_3d.h"
#include <QList>
#include <memory>

using Object3D = std::shared_ptr<IObject3D>;

///
/// \brief Объект групировки 3d объектов
/// \warning При удалении группы она удаляет все содержащиеся в ней объекты
///
class Group3D : public IObject3D
{
public:
    ///
    /// \brief Конструктор группы
    /// \param name имя группы
    ///
    Group3D( const QString &name = "" );
    ~Group3D();
public:

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

public:

    ///
    /// \brief Добавить объект к отрисовке
    /// \param obj объект
    ///
    void addObject( const Object3D obj );

    ///
    /// \brief Удалить объект
    /// \param obj объект
    ///
    void removeObject( const Object3D obj );

public:

    ///
    /// \brief Список отрисовываемых объектов
    ///
    QList<Object3D> __objects;
};

#endif // GROUP_3D_H
