#ifndef TRIANGLEOBJECT3D_H
#define TRIANGLEOBJECT3D_H

#include "../../i_object_3d.h"

///
/// \brief 3D объект базирущийся на списке треугольников
/// \details Необходим для простого корректного отображения
/// obj файла
///
class TriangleObject3D : public IObject3D
{
public:
    TriangleObject3D();
    ~TriangleObject3D();
public:

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

    ///
    /// \brief Метод инициализации текстуры
    /// \param texture текстура
    ///
    void initTexture( const QImage &texture );

    ///
    /// \brief Добавить треугольник
    /// \param vertData данные вершин
    ///
    void addTriangle( const QVector<VertexData> &vertData  );

    ///
    /// \brief Количество треугольников
    /// \return количество
    ///
    int triangleCount() const;

private:

    ///
    /// \brief Структура буфера треугольника
    ///
    struct TriangleBuffer {

        TriangleBuffer();
        TriangleBuffer( const QVector<VertexData> &vertData );
        ~TriangleBuffer();

        ///
        /// \brief Метод инициализации объекта
        /// \param vertData список вершин
        ///
        void init( const QVector<VertexData> &vertData );

        ///
        /// \brief Метод отрисовки объектов
        /// \param program программа шейдеров
        /// \param functions экземпляр функций openGL
        ///
        void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

        ///
        /// \brief Буфер вертексов
        ///
        QOpenGLBuffer   vertexBuffer;

        ///
        /// \brief Буфер индексов
        ///
        QOpenGLBuffer   indexBuffer;

    };

private:

    ///
    /// \brief Текстура объекта
    ///
    QOpenGLTexture          *__texture;

    QVector<TriangleBuffer *> __triangles;
};

#endif // TRIANGLEOBJECT3D_H
