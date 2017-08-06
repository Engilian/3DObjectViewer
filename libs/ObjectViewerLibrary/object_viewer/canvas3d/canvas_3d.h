#ifndef I_CANVAS_3D_H
#define I_CANVAS_3D_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QQuaternion>
#include <QMouseEvent>
#include <QTimer>

#include "../object3d/group/group_3d.h"
#include "../object3d/skybox/skybox_one_cube_texture.h"
#include "../object3d/skybox/skybox_six_textutes.h"
#include "../object3d/camera/camera_3d.h"

///
/// \brief Интерфейс окна рендера
///
class Canvas3D : public QOpenGLWidget
{
    Q_OBJECT
public:
    Canvas3D();
    ~Canvas3D();
public:

    ///
    /// \brief Список объектов для отрисовки
    /// \return список объектов 3d
    ///
    QList<Object3D> *objects();

protected:

    ///
    /// \brief Метод инициализации openGL
    ///
    void initializeGL();

    ///
    /// \brief Метод изменения размеров области вывода
    /// \param w новая ширина
    /// \param h новая высота
    ///
    void resizeGL(int w, int h);

    ///
    /// \brief Метод перерисовки
    ///
    void paintGL();

    ///
    /// \brief Метод инициализации шейдеров
    ///
    void initShaders();

protected:

    void mousePressEvent ( QMouseEvent *event );
    void mouseMoveEvent ( QMouseEvent *event );
    void wheelEvent ( QWheelEvent *event );

private:

    void __checkFps();

private:

    QMatrix4x4              __projection;
    QOpenGLShaderProgram    __shaderProgram;
    QOpenGLShaderProgram    __skyBoxShaderProgram;
    QVector2D               __mousePosition;
    QVector3D               __pos;
    QQuaternion             __rotate;

    Camera3D                *__mainCamera;
    ISkyBox                 *__skyBox;

    ///
    /// \brief Таймер перерисовки
    ///
    QTimer __repaintTimer;

    ///
    /// \brief Список объектов для отрисовки
    ///
    QList<Object3D> __objects;


    ///
    /// \brief Текущий fps
    ///
    int fps = 0;

    ///
    /// \brief Промежуточный расчет fps
    ///
    int __tempFps = 0;

signals:

public slots:
};

#endif // I_CANVAS_3D_H
