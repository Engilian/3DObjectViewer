#include "main_window.h"

#include <object_viewer/object3d/shapes/cube/example_cube_3d.h>
#include <object_viewer/object3d/object_loader/object_loader.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize( 1280, 800 );
    this->setCentralWidget( &__canvas );
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    Object3D cube = Object3D( new ExampleCube3d( 1 ) );
    cube.get()->translate( QVector3D( -2.0f, 0.0f, 0.0f ) );
    __canvas.objects()->append( cube );

    ObjectLoader loader;
    QList<IObject3D*> list = loader.load( ":/example/belka/belka.obj", ":/example/belka/belka.mtl" );

    for ( IObject3D *obj: list ) {

        Object3D obj_ptr( obj );
        __canvas.objects()->append( obj_ptr );
    }

    list.clear();

    list = loader.load( ":/example/suzanne.obj", ":/example/suzanne.mtl" );

    for ( IObject3D *obj: list ) {

        Object3D obj_ptr( obj );
        obj_ptr.get()->translate( QVector3D( 2.0f, 0.0f, 0.0f ) );
        __canvas.objects()->append( obj_ptr );
    }

    list.clear();
}
