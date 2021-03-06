#include "main_window.h"
#include "ui_main_window.h"

#include <QLayout>
#include <QKeyEvent>
#include <QInputDialog>
#include <QFileDialog>

#include <QDir>
#include <QFile>
#include <QCoreApplication>

#include <object_viewer/object3d/object_loader/object_loader.h>
#include <object_viewer/object3d/shapes/cube/example_cube_3d.h>
#include <object_viewer/object3d/group/group_3d.h>
#include <object_viewer/object3d/skybox/loader/skb/skb_loader.h>
#include <object_viewer/object3d/skybox/skybox_one_cube_texture.h>
#include <object_viewer/object3d/skybox/skybox_six_textutes.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    __viewer = new Viewer3D;

    __viewer->setFocus ();

    auto *lay = new QVBoxLayout;
    ui->centralWidget->setLayout ( lay );
    lay->addWidget ( __viewer );

    __scene = new Scene3D( __viewer );
    {
        connect ( __viewer, &Canvas3D::InitGL, this, &MainWindow::initDefaultScene );
    }

    {
        ui->object_list->setWidget ( &__listObjects );
        __listObjects.forEventFilter ()->installEventFilter ( this );
        __listObjects.installEventFilter ( this );
        ui->object_list->installEventFilter ( this );

        connect ( __scene, &SimpleScene3D::AddedObject3d, &__listObjects, &ListObject3d::AddedObject3d );
        connect ( __scene, &SimpleScene3D::RemovedObject3d, &__listObjects, &ListObject3d::RemovedObject3d );
    }

    ui->statusBar->addWidget ( &__fps, 10 );
    __fps.setAlignment ( Qt::AlignVCenter | Qt::AlignRight );
    connect ( __viewer, &Canvas3D::Fps, this, &MainWindow::_updateFps );


    __connectMenu ();
    QApplication::instance()->installEventFilter( this );
}

MainWindow::~MainWindow()
{
    if ( __scene ) {
        delete __scene;
    }

    if ( __viewer ) {
        delete __viewer;
    }

    delete ui;
}

void MainWindow::initDefaultScene()
{
    __viewer->initDefaultSkyBox ();
    __viewer->setViewingAngle ( 40 );

    createSquirrel();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED( watched );

    if ( event->type() == QEvent::KeyPress ) {


        keyHandler( dynamic_cast<QKeyEvent*>( event ) );

    }

    return QMainWindow::eventFilter( watched, event );
}

void MainWindow::__connectMenu()
{
    connect ( ui->menu_skybox->actions ().at ( 0 ), SIGNAL(triggered(bool)), this, SLOT(loadSkyBox()) );
    connect ( ui->menu_skybox->actions ().at ( 1 ), SIGNAL(triggered(bool)), this, SLOT(loadSkyBoxOneFile()) );
    connect ( ui->menu_skybox->actions ().at ( 2 ), SIGNAL(triggered(bool)), this, SLOT(loadSkyBoxSixFile()) );
    connect ( ui->menu_skybox->actions ().at ( 4 ), SIGNAL(triggered(bool)), this, SLOT(createDefaultSkyBox()) );
    connect ( ui->menu_skybox->actions ().at ( 6 ), SIGNAL(triggered(bool)), this, SLOT(clearSkyBox()) );

    connect ( ui->menu_obj->actions ().at ( 0 ), SIGNAL(triggered(bool)), this, SLOT(loadObject()) );
    connect ( ui->menu_obj->actions ().at ( 2 ), SIGNAL(triggered(bool)), this, SLOT(createSquirrel()) );
    connect ( ui->menu_obj->actions ().at ( 3 ), SIGNAL(triggered(bool)), this, SLOT(createCube()) );
    connect ( ui->menu_obj->actions ().at ( 4 ), SIGNAL(triggered(bool)), this, SLOT(createMonkey()) );
    connect ( ui->menu_obj->actions ().at ( 6 ), SIGNAL(triggered(bool)), this, SLOT(createSquirrelsArmy()) );
    connect ( ui->menu_obj->actions ().at ( 8 ), SIGNAL(triggered(bool)), this, SLOT(clearObjects()) );
}

void MainWindow::keyHandler(QKeyEvent *event)
{
    float stepTranslate = 0.05f;

    if ( event->key () == Qt::Key_W ) {

        QVector3D vector( 0.0f, 0.0f, stepTranslate );
        __viewer->mainCamera ()->move ( vector );
    }

    if ( event->key () == Qt::Key_S ) {

        QVector3D vector( 0.0f, 0.0f, -stepTranslate );
        __viewer->mainCamera ()->move ( vector );
    }

    if ( event->key () == Qt::Key_A ) {

        QVector3D vector( stepTranslate, 0.0f, 0.0f );
        __viewer->mainCamera ()->move ( vector );
    }

    if ( event->key () == Qt::Key_D ) {

        QVector3D vector( -stepTranslate, 0.0f, 0.0f );
        __viewer->mainCamera ()->move ( vector );
    }

    if ( event->key () == Qt::Key_Q ) {

        QVector3D axis = QVector3D( 0, 0, 0.05f );
        __viewer->mainCamera ()->rotate( QQuaternion::fromAxisAndAngle ( axis, -5 ) );
    }

    if ( event->key () == Qt::Key_E ) {

        QVector3D axis = QVector3D( 0, 0, 0.05f );
        __viewer->mainCamera ()->rotate( QQuaternion::fromAxisAndAngle ( axis, 5 ) );
    }

    if ( event->key () == Qt::Key_Comma ) {

        QVector3D axis = QVector3D( 0, 0.05f, 0.0f );
        __viewer->mainCamera ()->rotate( QQuaternion::fromAxisAndAngle ( axis, -0.5 ) );
    }

    if ( event->key () == Qt::Key_Period ) {

        QVector3D axis = QVector3D( 0, 0.05f, 0.0f );
        __viewer->mainCamera ()->rotate( QQuaternion::fromAxisAndAngle ( axis, 0.5 ) );
    }
}

void MainWindow::_updateFps(int fps)
{
    __fps.setText ( QString::number ( fps ) + " fp/s" );
}

void MainWindow::clearObjects()
{
    qDebug() << "Clear Objects";
    __scene->clearObjects ();
}

void MainWindow::clearSkyBox()
{
    qDebug() << "Clear SkyBox";
    __viewer->destroySkyBox ();
}

void MainWindow::loadSkyBox()
{
    QFileDialog dialog( this, "Choice my *.skb file" );
    dialog.setFilter ( QDir::Files );
    dialog.setDirectory ( QDir::fromNativeSeparators(
                              QApplication::applicationDirPath () + "/res" ) );
    dialog.setNameFilter(tr("Skybox xml file (*.skb)"));
    dialog.setMinimumSize ( 800, 600 );

    if ( dialog.exec () ) {
        qDebug() << dialog.selectedFiles ().first ();

        SkbLoader loader;

        auto *skybox = loader.load ( dialog.selectedFiles ().first () );

        if ( skybox ) {

            __viewer->destroySkyBox ();
            __viewer->setSkyBox ( skybox );
        }
    }
}

void MainWindow::loadSkyBoxOneFile()
{
    QFileDialog dialog( this, "Choice skybox file" );
    dialog.setFilter ( QDir::Files );
    dialog.setDirectory ( QDir::fromNativeSeparators(
                              QApplication::applicationDirPath () + "/res" ) );
    dialog.setMinimumSize ( 800, 600 );

    if ( dialog.exec() )
    {
        auto *skybox = new SkyBoxOneCubeTexture( 10.0f,
                                                 dialog.selectedFiles().first() );

        __viewer->destroySkyBox ();
        __viewer->setSkyBox ( skybox );
    }
}

void MainWindow::loadSkyBoxSixFile()
{
    qDebug() << "Load skybox six texture";
}

void MainWindow::createDefaultSkyBox()
{
    __scene->viewPort ()->destroySkyBox ();
    __scene->viewPort ()->initDefaultSkyBox ();
}

void MainWindow::loadObject()
{
    QFileDialog dialog( this, "Choice *.obj file" );
    dialog.setFilter ( QDir::Files );
    dialog.setDirectory ( QDir::fromNativeSeparators(
                              QApplication::applicationDirPath () + "/res" ) );
    dialog.setNameFilter(tr("Wavefront file (*.obj)"));
    dialog.setMinimumSize ( 800, 600 );

    if ( dialog.exec () ) {
        qDebug() << dialog.selectedFiles ().first ();

        ObjectLoader loader;

        QFileInfo objInfo ( dialog.selectedFiles ().first () );
        QDir dir = objInfo.dir ();

        QList<IObject3D*> objects = loader.load ( dialog.selectedFiles ().first (), dir.absoluteFilePath ( objInfo.fileName ().remove ( ".obj" ) + ".mtl" ) );

        auto *group = new Group3D( objInfo.fileName () );
        Object3D obj( group );

        for ( IObject3D *o: objects ) {

            group->addObject ( Object3D( o ) );
        }

        __scene->addObject ( obj );
    }
}

void MainWindow::createSquirrelsArmy()
{
    bool ok = false;

    int armySize = QInputDialog::getInt ( this, "Choise army size", "size", 1, 1, 100, 1, &ok  );

    if ( !ok ) return;

    int rowLength = QInputDialog::getInt ( this, "Choise row length", "length", armySize, 1, 100, 1, &ok  );

    if ( !ok ) return;

    float step = QInputDialog::getDouble ( this, "Choice offset", "offset", 1.5f, 0.0, 600.0f, 1, &ok );

    if  ( !ok ) return;

    Group3D *group = new Group3D( "My little army!" );
    ObjectLoader loader;

    float posX = ( rowLength * ( 1.0 * step ) ) / 2;
    QVector3D pos( 0.0, 0.0, 0.0 );

    QString model = QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/models/belka/belka.obj"
                );

    QString material = QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/models/belka/belka.mtl"
                );

    for ( int i = 0; i < armySize; ++i ) {

        if ( i % rowLength == 0 && i > 0 ) {

            pos += QVector3D( 0.0, 0.0, step );
            pos.setX ( 0.0 );
        }

        QList<IObject3D*> list = loader.load( model, material );
        QApplication::processEvents ();

        for ( IObject3D *obj: list ) {

            obj->setName ( obj->name () );
            obj->translate ( pos );
            Object3D obj_ptr( obj );
            group->addObject ( obj_ptr );
            QApplication::processEvents ();
        }

        pos += QVector3D( step, 0.0, 0.0 );

        QApplication::processEvents ();
    }

    group->translate ( QVector3D( -posX, 0.0, 0.0 ) );
    __scene->addObject ( Object3D( group ) );
}

void MainWindow::createSquirrel()
{
    ObjectLoader loader;

    QString model = QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/models/belka/belka.obj"
                );

    QString material = QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/models/belka/belka.mtl"
                );

    QList<IObject3D*> list = loader.load( model, material );

    for ( IObject3D *obj: list ) {

        obj->setName ( obj->name () );
        Object3D obj_ptr( obj );
        __scene->addObject ( obj_ptr );
    }
}

void MainWindow::createCube()
{
    Object3D obj( new  ExampleCube3d() );
    __scene->addObject ( obj );
}

void MainWindow::createMonkey()
{
    ObjectLoader loader;

    QString model = QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/models/suzanne.obj"
                );

    QString material = QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/models/suzanne.mtl"
                );

    QList<IObject3D*> list = loader.load( model, material );

    for ( IObject3D *obj: list ) {

        obj->setName ( obj->name () );
        Object3D obj_ptr( obj );
        __scene->addObject ( obj_ptr );
    }
}
