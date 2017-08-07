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

public:

    ///
    /// \brief Скайбокс
    ///
    ISkyBox *skybox() const;

    ///
    /// \brief Установить скайбокс
    /// \param skybox скайбокс
    ///
    void setSkyBox( ISkyBox *skybox );

    ///
    /// \brief Уничтожить скайбокс
    ///
    void destroySkyBox();

    ///
    /// \brief Инициализировать skybox по умолчнию
    ///
    void initDefaultSkyBox();

public:

    ///
    /// \brief Получить камеру
    /// \return камера
    ///
    Camera3D *mainCamera() const;

    ///
    /// \brief fps
    ///
    int fps() const;

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

    void mouseReleaseEvent ( QMouseEvent *event );
    void mousePressEvent ( QMouseEvent *event );
    void mouseMoveEvent ( QMouseEvent *event );
    void wheelEvent ( QWheelEvent *event );

private:

    ///
    /// \brief Метод подсчета fps
    ///
    void __checkFps();

private:

    ///
    /// \brief Матрица проекции
    ///
    QMatrix4x4              __projection;

    ///
    /// \brief Основной шейдер для объектов
    ///
    QOpenGLShaderProgram    __shaderProgram;

    ///
    /// \brief Шейдр для skybox
    ///
    QOpenGLShaderProgram    __skyBoxShaderProgram;

    ///
    /// \brief Полседняя позиция мыши
    ///
    QVector2D               __mousePosition;

    ///
    /// \brief Камера для отображения
    ///
    Camera3D                *__mainCamera;

    ///
    /// \brief Скайбокс
    ///
    ISkyBox                 *__skyBox;

    ///
    /// \brief Таймер перерисовки
    ///
    QTimer                  __repaintTimer;

    ///
    /// \brief Список объектов для отрисовки
    ///
    QList<Object3D>         __objects;


    ///
    /// \brief Текущий fps
    ///
    int __fps = 0;

    ///
    /// \brief Промежуточный расчет fps
    ///
    int __tempFps = 0;

signals:

    void Fps( int fps );

public slots:
};

#endif // I_CANVAS_3D_H
