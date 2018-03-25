#include "skybox_six_textutes.h"

#include <QDir>
#include <QString>
#include <QCoreApplication>

namespace
{

QString getTexturePath( const QString &fileName )
{

    return QDir::fromNativeSeparators(
                QCoreApplication::applicationDirPath() +
                "/res/textures/skybox/cube_six_textures/" +
                fileName
                );
}

};

SkyBoxSixTextutes::SkyBoxSixTextutes(float size)
{
    const QStringList paths = { getTexturePath ( "back.png" ),
                                getTexturePath ( "right.png" ),
                                getTexturePath ( "up.png" ),
                                getTexturePath ( "front.png" ),
                                getTexturePath ( "left.png" ),
                                getTexturePath ( "down.png" ) };

    __init( size, paths );
}

SkyBoxSixTextutes::SkyBoxSixTextutes(float size, QStringList textures)
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
    for ( SimpleObject3d_v1 *obj: __planes ) {
        obj->draw( program, functions );
    }
}

void SkyBoxSixTextutes::__init(float size, QStringList textures)
{
    float width_div_2 = size / 2.0f;
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    // Сзади
    vertexes.append( VertexData( QVector3D( -width_div_2, width_div_2, width_div_2 ),   QVector2D( 0.0f, 1.0f ), QVector3D( 0.0, 0.0, -1.0 ) ) );
    vertexes.append( VertexData( QVector3D( -width_div_2, -width_div_2, width_div_2 ),  QVector2D( 0.0f, 0.0f ), QVector3D( 0.0, 0.0, -1.0 ) ) );
    vertexes.append( VertexData( QVector3D( width_div_2,  width_div_2, width_div_2 ),   QVector2D( 1.0f, 1.0f ), QVector3D( 0.0, 0.0, -1.0 ) ) );
    vertexes.append( VertexData( QVector3D( width_div_2,  -width_div_2, width_div_2 ),  QVector2D( 1.0f, 0.0f ), QVector3D( 0.0, 0.0, -1.0 ) ) );

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d_v1( vertexes, indexes, textures[0] ) );

    vertexes.clear();
    indexes.clear();

    // Справа
    vertexes.append( VertexData( QVector3D( width_div_2, width_div_2, width_div_2 ),    QVector2D( 0.0f, 1.0f ), QVector3D( -1.0, 0.0, 0.0)) );
    vertexes.append( VertexData( QVector3D( width_div_2, -width_div_2, width_div_2 ),   QVector2D( 0.0f, 0.0f ), QVector3D( -1.0, 0.0, 0.0)) );
    vertexes.append( VertexData( QVector3D( width_div_2, width_div_2, -width_div_2 ),   QVector2D( 1.0f, 1.0f ), QVector3D( -1.0, 0.0, 0.0)) );
    vertexes.append( VertexData( QVector3D( width_div_2, -width_div_2, -width_div_2 ),  QVector2D( 1.0f, 0.0f ), QVector3D( -1.0, 0.0, 0.0)) );

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d_v1( vertexes, indexes, textures[1] ) );

    vertexes.clear();
    indexes.clear();

    // Сверху
    vertexes.append(VertexData( QVector3D( width_div_2, width_div_2, width_div_2 ),     QVector2D( 0.0f, 1.0f ), QVector3D( 0.0, -1.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( width_div_2, width_div_2, -width_div_2 ),    QVector2D( 0.0f, 0.0f ), QVector3D( 0.0, -1.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, width_div_2, width_div_2 ),    QVector2D( 1.0f, 1.0f ), QVector3D( 0.0, -1.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, width_div_2, -width_div_2 ),   QVector2D( 1.0f, 0.0f ), QVector3D( 0.0, -1.0, 0.0 ) ) );

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d_v1( vertexes, indexes, textures[2] ) );

    vertexes.clear();
    indexes.clear();

    // Спереди
    vertexes.append(VertexData( QVector3D( width_div_2, width_div_2, -width_div_2 ),    QVector2D( 0.0f, 1.0f ), QVector3D( 0.0, 0.0, 1.0 ) ) );
    vertexes.append(VertexData( QVector3D( width_div_2, -width_div_2, -width_div_2 ),   QVector2D( 0.0f,0.0f ), QVector3D( 0.0, 0.0, 1.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, width_div_2, -width_div_2 ),   QVector2D( 1.0f, 1.0f ), QVector3D( 0.0, 0.0, 1.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, -width_div_2, -width_div_2 ),  QVector2D( 1.0f,0.0f ), QVector3D( 0.0, 0.0, 1.0 ) ) );

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d_v1( vertexes, indexes, textures[3] ) );

    vertexes.clear();
    indexes.clear();


    // Слева
    vertexes.append(VertexData( QVector3D( -width_div_2, width_div_2, -width_div_2 ),   QVector2D( 0.0f, 1.0f ), QVector3D( 1.0, 0.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, -width_div_2, -width_div_2 ),  QVector2D( 0.0f, 0.0f ), QVector3D( 1.0, 0.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, width_div_2, width_div_2 ),    QVector2D( 1.0f, 1.0f ), QVector3D( 1.0, 0.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, -width_div_2, width_div_2 ),   QVector2D( 1.0f, 0.0f ), QVector3D( 1.0, 0.0, 0.0 ) ) );

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d_v1( vertexes, indexes, textures[4] ) );

    vertexes.clear();
    indexes.clear();


    // Снизу
    vertexes.append(VertexData( QVector3D( width_div_2, -width_div_2, -width_div_2 ),   QVector2D( 0.0f, 1.0f ), QVector3D( 0.0, 1.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( width_div_2, -width_div_2, width_div_2 ),    QVector2D( 0.0f, 0.0f ), QVector3D( 0.0, 1.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, -width_div_2, -width_div_2 ),  QVector2D( 1.0f, 1.0f ), QVector3D( 0.0, 1.0, 0.0 ) ) );
    vertexes.append(VertexData( QVector3D( -width_div_2, -width_div_2, width_div_2 ),   QVector2D( 1.0f, 0.0f ), QVector3D( 0.0, 1.0, 0.0 ) ) );

    for ( int i = 0; i < 6; ++i ) {

        indexes.append ( 0 );
        indexes.append ( 2 );
        indexes.append ( 1 );

        indexes.append ( 2 );
        indexes.append ( 3 );
        indexes.append ( 1 );
    }

    __planes.append( new SimpleObject3d_v1( vertexes, indexes, textures[5] ) );

    vertexes.clear();
    indexes.clear();
}
