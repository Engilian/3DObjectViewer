#include "main_window.h"

#include <object_viewer/object3d/shapes/cube/example_cube_3d.h>
#include <object_viewer/object3d/object_loader/object_loader.h>
#include <QApplication>

#include "load_object_runnuble.h"
#include <QThreadPool>

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


    __canvas.initDefaultSkyBox ();
    initBelka ();
    initCubes ();

    //    QThreadPool::globalInstance ()->start ( new LoadObjectRunnuble( this ) );
}

void MainWindow::initCubes()
{
    int width = 6;

    float startX = -width / 2.0f;
    float startY = -10.0f;
    float startZ = 0.0f;

    QVector3D pos( startX, startY, startZ );

    for ( int z = 0; z < 2; ++z ) {

        for ( int y = 0; y < 4; ++y ) {

            for ( int x = 0; x < 6; ++x ) {

                Object3D obj = Object3D( new ExampleCube3d( 1 ) );
                obj.get ()->translate ( pos );
                __canvas.objects ()->append ( obj );

                pos += QVector3D( 1.5f, 0.0f, 0.0f  );
                QApplication::processEvents ();
            }

            pos.setX ( startX );
            pos += QVector3D( 0.0f, 1.5f, 0.0f  );
        }

        pos.setY ( startY );
        pos += QVector3D( 0.0f, 0.0f, 1.5f  );
    }
}

void MainWindow::initBelka()
{

    ObjectLoader loader;

    int width = 6;

    QVector3D pos( - width / 2.0f, 0.0f, 0.0f );
    for ( int i = 0; i < 12; ++i ) {

        if ( i % width == 0 && i != 0 ) {

            pos += QVector3D( 0.0f, 0.0f, 2.0f  );
            pos.setX ( - width / 2.0f );
        }

        QList<IObject3D*> list = loader.load( ":/example/belka/belka.obj", ":/example/belka/belka.mtl" );

        for ( IObject3D *obj: list ) {

            obj->translate ( pos );
            obj->setName ( obj->name () + QString::number ( i ) );
            Object3D obj_ptr( obj );
            __canvas.objects()->append( obj_ptr );

            QApplication::processEvents ();
        }

        pos += QVector3D( 1.5f, 0.0f, 0.0f  );

        QApplication::processEvents ();
    }

}
