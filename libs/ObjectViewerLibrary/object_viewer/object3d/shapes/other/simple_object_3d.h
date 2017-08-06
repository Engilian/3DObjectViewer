#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include "../../i_object_3d.h"

///
/// \brief Класс простого 3d объекта
///
class SimpleObject3d: public IObject3D
{
public:

    ///
    /// \brief Конструктор
    ///
    SimpleObject3d();

    ///
    /// \brief Конструктор с вызовом метода инициализации
    /// \param vertData список вершин
    /// \param indexes список индексов
    /// \param texture текстура
    ///
    SimpleObject3d(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture);

    ///
    /// \brief Деструктор
    /// \details виртуальный для наследования простых объектов
    ///
    virtual ~SimpleObject3d();

public:

    ///
    /// \brief Метод инициализации объекта
    /// \param vertData список вершин
    /// \param indexes список индексов
    /// \param texture текстура
    ///
    void init(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture);

    ///
    /// \brief Метод отрисовки объектов
    /// \param program программа шейдеров
    /// \param functions экземпляр функций openGL
    ///
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

private:

    ///
    /// \brief Буфер вертексов
    ///
    QOpenGLBuffer   __vertexBuffer;

    ///
    /// \brief Буфер индексов
    ///
    QOpenGLBuffer   __indexBuffer;

    ///
    /// \brief Текстура
    ///
    QOpenGLTexture  *__texture;
};

#endif // SIMPLEOBJECT3D_H
