#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <object_viewer/canvas3d/canvas_3d.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:

    void init();

    void initCubes();

    void initBelka();

private:

    Canvas3D __canvas;
};

#endif // MAIN_WINDOW_H
