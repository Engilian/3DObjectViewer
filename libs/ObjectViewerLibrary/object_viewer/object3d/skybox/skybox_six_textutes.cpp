#include "skybox_six_textutes.h"

SkyBoxSixTextutes::SkyBoxSixTextutes(float size)
{
    const QStringList paths = { ":/example/skybox/cube_six_textures/back.png",
                                ":/example/skybox/cube_six_textures/right.png",
                                ":/example/skybox/cube_six_textures/up.png",
                                ":/example/skybox/cube_six_textures/front.png",
                                ":/example/skybox/cube_six_textures/left.png",
                                ":/example/skybox/cube_six_textures/down.png" };

    QList<QImage> textures;

    for ( const QString &path: paths ) {
        textures << QImage( path );
    }

    __init( size, textures );
}

SkyBoxSixTextutes::SkyBoxSixTextutes(float size, QList<QImage> textures)
{

    __init( size, textures );
}

SkyBoxSixTextutes::~SkyBoxSixTextutes()
{
    while ( !__planes.isEmpty() ) {
        delete __planes.takeFirst();
    }
}

void SkyBoxSixTextutes::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    for ( SimpleObject3d *obj: __planes ) {
        obj->draw( program, functions );
    }
}

void SkyBoxSixTextutes::__init(float size, QList<QImage> textures)
{
    float width_div_2 = size / 2.0f;
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    // Сзади
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 0.0f), QVector3D(0.0, 0.0, -1.0)));

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d( vertexes, indexes, textures[0] ) );

    vertexes.clear();
    indexes.clear();

    // Справа
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 0.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1.0f, 1.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f, 0.0f), QVector3D(-1.0, 0.0, 0.0)));

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d( vertexes, indexes, textures[1] ) );

    vertexes.clear();
    indexes.clear();

    // Сверху
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f,0.0f), QVector3D(0.0, -1.0, 0.0)));

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d( vertexes, indexes, textures[2] ) );

    vertexes.clear();
    indexes.clear();

    // Спереди
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0f,0.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f,0.0f), QVector3D(0.0, 0.0, 1.0)));

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d( vertexes, indexes, textures[3] ) );

    vertexes.clear();
    indexes.clear();


    // Слева
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 1.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 0.0f), QVector3D(1.0, 0.0, 0.0)));

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d( vertexes, indexes, textures[4] ) );

    vertexes.clear();
    indexes.clear();

//    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0, -1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f,0.0f), QVector3D(0.0, -1.0, 0.0)));

    // Снизу
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d( vertexes, indexes, textures[5] ) );

    vertexes.clear();
    indexes.clear();
}
