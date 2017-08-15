#ifndef SIMPLE_OBJECT_3D_V1_H
#define SIMPLE_OBJECT_3D_V1_H

#include "../../i_object_3d.h"
#include "texture/texture_creator.h"


///
/// \brief Класс простого 3d объекта
///
class SimpleObject3d_v1: public IObject3D
{
public:

    ///
    /// \brief Конструктор
    ///
    SimpleObject3d_v1();

    ///
    /// \brief Конструктор с вызовом метода инициализации
    /// \param vertData список вершин
    /// \param indexes список индексов
    /// \param texture текстура
    ///
    SimpleObject3d_v1(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QString &texture);

    ///
    /// \brief Деструктор
    /// \details виртуальный для наследования простых объектов
    ///
    virtual ~SimpleObject3d_v1();

public:

    ///
    /// \brief Метод инициализации объекта
    /// \param vertData список вершин
    /// \param indexes список индексов
    /// \param texture текстура
    ///
    void init(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QString &texture);

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
    GlTexturePtr    __texture;
};

#endif // SIMPLE_OBJECT_3D_V1_H
