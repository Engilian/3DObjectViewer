#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <object_viewer/canvas3d/canvas_3d.h>
#include <object_viewer/scene3d/scene_3d.h>

#include "listObject3d/list_object3d.h"

namespace Ui {
class MainWindow;
}

///
/// \brief Структура перемещения
///
struct MoveStruct {
    bool moveForward    = false;
    bool moveBack       = false;
    bool moveLeft       = false;
    bool moveRight      = false;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

    ///
    /// \brief Инициализация сцены по умолчанию
    ///
    void initDefaultScene();

protected:

    bool eventFilter (QObject *watched, QEvent *event);

    void keyPressEvent (QKeyEvent *event);

private:

    ///
    /// \brief Подключение событий меню
    ///
    void __connectMenu();


private:
    Ui::MainWindow *ui;

    ListObject3d __listObjects;

    QLabel __fps;

private:

    ///
    /// \brief Окно вывода 3d
    ///
    Viewer3D            *__viewer;

    ///
    /// \brief Сцена 3д
    ///
    Scene3D             *__scene;

    ///
    /// \brief Таймер инициализации
    ///
    QTimer              __initSceneTimer;

private slots:

    void __initDefaultScene ();

    void __updateFps( int fps );

private slots:

    void __clearObjects();

    void __clearSkyBox();

private slots:

    void __loadSkyBox();

    void __loadSkyBoxOneFile();

    void __loadSkyBoxSixFile();

    void __createDefaultSkyBox();

private slots:

    void __loadObject();

    void __createSquirrelsArmy ();

    void __createSquirrel();

    void __createCube();

    void __createMonkey();


};

#endif // MAIN_WINDOW_H
