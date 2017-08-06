#ifndef I_OBJECT_3D_H
#define I_OBJECT_3D_H

#include <QString>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLContext>
#include <QOpenGLTexture>

#include "i_transformational.h"


///
/// \brief Структура описывающая вертекс
///
struct VertexData
{
    VertexData(){}

    ///
    /// \brief Конструктор
    /// \param p координата точки
    /// \param t текстурная координата
    /// \param n координата нормали
    ///
    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p), texture(t), normal(n)
    {}

    ///
    /// \brief Позиция
    ///
    QVector3D position;

    ///
    /// \brief Текстурная координата
    ///
    QVector2D texture;

    ///
    /// \brief Координата нормали
    ///
    QVector3D normal;
};

///
/// \brief Интерфейс 3d объекта
///
class IObject3D: public ITransformational
{
protected:
    IObject3D();
public:
    virtual ~IObject3D();
public:

    ///
    /// \brief Имя объекта
    /// \return имя
    ///
    virtual QString name() const;

    ///
    /// \brief Установить имя объекта
    /// \param name имя
    ///
    virtual void setName( const QString name );

public:

    void rotate( const QQuaternion &q );
    void translate( const QVector3D &t );
    void scale( const float scale );
    void setGlobalTransform( const QMatrix4x4 &m );

    ///
    /// \brief Создать модельную матрицу
    /// \return модельная матрица
    ///
    QMatrix4x4 createModelMatrix() const;

protected:

    ///
    /// \brief Поворот
    ///
    QQuaternion     _rotate;

    ///
    /// \brief Перемещение
    ///
    QVector3D       _translate;

    ///
    /// \brief Маштаб
    ///
    float           _scale              = 1.0f;

    ///
    /// \brief Глобальные преобразования
    ///
    QMatrix4x4      _globalTransform;

private:

    ///
    /// \brief Имя объекта
    ///
    QString __objectName;

};

#endif // I_OBJECT_3D_H
