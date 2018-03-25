#include "canvas_3d.h"
#include <QColor>
#include <QPainter>
#include <thread>

Canvas3D::Canvas3D() : QOpenGLWidget(), __mainCamera(0), __skyBox(0)
{
    connect ( &__repaintTimer, SIGNAL(timeout()), this, SLOT(updateCanvas()));
    __repaintTimer.start ( 1000.0 / 60.0  );

    std::thread th( std::bind( &Canvas3D::__checkFps, this ) );
    th.detach ();
}

Canvas3D::~Canvas3D()
{
    if ( __mainCamera ) {
        delete __mainCamera;
    }

    if ( __skyBox ) {
        delete __skyBox;
    }

    if ( __threadRunInfo.isActive ) {

        __threadRunInfo.isActive = false;

        while ( __threadRunInfo.isRuning ) std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    }
}

QList<Object3D> *Canvas3D::objects()
{
    return &__objects;
}

ISkyBox *Canvas3D::skybox() const
{
    return __skyBox;
}

void Canvas3D::setSkyBox(ISkyBox *skybox)
{
    __skyBox = skybox;
}

void Canvas3D::destroySkyBox()
{
    if ( __skyBox ) {

        delete __skyBox;
        __skyBox = nullptr;
    }
}

void Canvas3D::initDefaultSkyBox()
{
    __skyBox = new SkyBoxSixTextutes( 500.0f );
}

Camera3D *Canvas3D::mainCamera() const
{
    return __mainCamera;
}

void Canvas3D::initializeGL()
{
    QColor clearColor( Qt::black );
    glClearColor( clearColor.red(), clearColor.green(), clearColor.blue(), 1 );

    glEnable( GL_DEPTH_TEST );
//    glEnable( GL_CULL_FACE );

    initShaders();

    __mainCamera = new Camera3D();
    __mainCamera->translate( QVector3D( 0.0f, 0.0f, -10.0f ) );

    emit InitGL();
}

void Canvas3D::resizeGL(int w, int h)
{
    float aspect = w / (float)h;

    __projection.setToIdentity();
    __projection.perspective( __viewingAngle, aspect, 0.1f, 2000.0f );
}

void Canvas3D::paintGL()
{
    ++__tempFps;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Отрисовка скайбокса
    if ( __skyBox ) {

        __skyBoxShaderProgram.bind();
        if ( __mainCamera ) __mainCamera->draw( &__skyBoxShaderProgram, context()->functions() );
        __skyBoxShaderProgram.setUniformValue("u_projectionMatrix", __projection);
        __skyBox->draw( &__skyBoxShaderProgram, context()->functions() );
        __skyBoxShaderProgram.release();
    }

    // Отрисовка объектов

    __shaderProgram.bind();
    __shaderProgram.setUniformValue("u_projectionMatrix", __projection);
    __shaderProgram.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 10.0)); // x,y,z,1.0 - так как вершина а не вектор
    __shaderProgram.setUniformValue("u_lightPower", 5.0f);
    __shaderProgram.setUniformValue("u_colorSpecular", QVector4D(1.0, 0.0, 1.0, 1.0)); // цвет бликов

    if ( __mainCamera ) __mainCamera->draw( &__shaderProgram, context()->functions() );

    for ( const Object3D &obj: __objects ) {
        obj.get()->draw( &__shaderProgram, context()->functions() );
    }

    __shaderProgram.release();

    __waitToUpdate = false;
}

void Canvas3D::initShaders()
{
    if ( !__shaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex, ":/default_vertex_shader.vsh" ) ) {
        close();
    }

    if ( !__shaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment, ":/default_fragmen_shader.fsh" ) ) {
        close();
    }

    if ( !__shaderProgram.link() ) {
        close();
    }

    if ( !__skyBoxShaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex, ":/skybox.vsh" ) ) {
        close();
    }

    if ( !__skyBoxShaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment, ":/skybox.fsh" ) ) {
        close();
    }

    if ( !__skyBoxShaderProgram.link() ) {
        close();
    }
}

void Canvas3D::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->buttons () == Qt::RightButton ) {

        if ( __mainCamera ) __mainCamera->resetRotation ();
    }
}

void Canvas3D::mousePressEvent ( QMouseEvent *event )
{
    if ( event->buttons () == Qt::LeftButton || event->button () == Qt::MidButton) {

        __mousePosition = QVector2D ( event->localPos () );
    }
    else if ( event->buttons () == Qt::RightButton ) {

        if ( __mainCamera ) __mainCamera->resetRotation ();
    }

    event->accept ();
}

void Canvas3D::mouseMoveEvent ( QMouseEvent *event )
{
    if ( event->buttons () == Qt::LeftButton ) {

        QVector2D diff = QVector2D( event->localPos () ) - __mousePosition;
        __mousePosition = QVector2D( event->localPos () );

        QVector2D diffX = QVector2D( diff.x(), 0 );
        QVector2D diffY = QVector2D( 0, diff.y() );

        float angleX = diffX.length () / 2.0f;
        float angleY = diffY.length () / 2.0f;

        QVector3D axisX = QVector3D( diffX.y (), diffX.x (), 0.0 );
        __mainCamera->rotate( QQuaternion::fromAxisAndAngle ( axisX, angleX ) );

        QVector3D axisY = QVector3D( diffY.y (), diffY.x (), 0.0 );
        __mainCamera->rotate( QQuaternion::fromAxisAndAngle ( axisY, angleY ) );
    }
    else if ( event->buttons () == Qt::MidButton ) {

        QVector2D diff = QVector2D( event->localPos () ) - __mousePosition;
        __mousePosition = QVector2D( event->localPos () );

        QVector3D vector( diff.x () / 250.0f, -diff.y () / 250.0f, 0 );
        __mainCamera->move( vector );
    }
}

void Canvas3D::wheelEvent ( QWheelEvent *event )
{


    if ( event->delta() > 0 ) {
        QVector3D vector( 0.0, 0.0, 0.25 );
        __mainCamera->move( vector );
    }
    else if ( event->delta() < 0 ) {
        QVector3D vector( 0.0, 0.0, -0.25 );
        __mainCamera->move( vector );
    }
}

void Canvas3D::__checkFps()
{
    __threadRunInfo.isActive = true;
    __threadRunInfo.isRuning = true;

    while ( __threadRunInfo.isActive ) {

        __fps = __tempFps;
        __tempFps = 0;
        emit Fps ( __fps );

        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }

    __threadRunInfo.isRuning = false;
}

void Canvas3D::updateCanvas()
{
    if  ( !__waitToUpdate ) {
        __waitToUpdate = true;
        update ();
    }
}

int Canvas3D::viewingAngle() const
{
    return __viewingAngle;
}

void Canvas3D::setViewingAngle(int viewingAngle)
{
    __viewingAngle = viewingAngle;

    resizeGL ( width (), height () );
}

int Canvas3D::fps() const
{
    return __fps;
}
