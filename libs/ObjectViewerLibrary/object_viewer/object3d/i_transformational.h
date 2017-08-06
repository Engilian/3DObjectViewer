#ifndef I_TRANSFORMATIONAL_H
#define I_TRANSFORMATIONAL_H

class QMatrix4x4;
class QVector3D;
class QQuaternion;
class QOpenGLShaderProgram;
class QOpenGLFunctions;

///
/// \brief Интерфейс трансформации
///
class ITransformational {
protected:
    ITransformational(){}
public:
    virtual ~ITransformational(){}
public:

    ///
    /// \brief Повернуть объект
    /// \param q кваторнион поаорота
    ///
    virtual void rotate( const QQuaternion &q ) = 0;

    ///
    /// \brief Установить перемещение
    /// \param t вектор перемещения
    ///
    virtual void translate( const QVector3D &t ) = 0;

    ///
    /// \brief Установить масштаб
    /// \param scale масштаб
    ///
    virtual void scale( const float scale ) = 0;

    ///
    /// \brief Установка глобальной матрицы
    /// \param m матрица
    ///
    virtual void setGlobalTransform( const QMatrix4x4 &m ) = 0;

    ///
    /// \brief Метод отрисовки объектов
    /// \param program программа шейдеров
    /// \param functions экземпляр функций openGL
    ///
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions) = 0;

};

#endif // I_TRANSFORMATIONAL_H
