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
private:

    ///
    /// \brief Подключение событий меню
    ///
    void __connectMenu();

    void keyHandler( QKeyEvent *event );


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

private slots:
    void _updateFps( int fps );

public slots:

    void clearObjects();

    void clearSkyBox();

    void loadSkyBox();
    void loadSkyBoxOneFile();
    void loadSkyBoxSixFile();
    void createDefaultSkyBox();

    void loadObject();
    void createSquirrelsArmy ();
    void createSquirrel();
    void createCube();
    void createMonkey();


};

#endif // MAIN_WINDOW_H
