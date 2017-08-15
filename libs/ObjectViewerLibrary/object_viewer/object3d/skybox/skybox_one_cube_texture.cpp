#include "skybox_one_cube_texture.h"

SkyBoxOneCubeTexture::SkyBoxOneCubeTexture( float width, QString texture)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;

    // Сзади
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 2.0f / 3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 1.0f / 3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(3.0f / 4.0f, 2.0f / 3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(3.0f / 4.0f, 1.0f / 3.0f), QVector3D(0.0, 0.0, -1.0)));

    // Справа
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(3.0f / 4.0f, 2.0f / 3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(3.0f / 4.0f, 1.0f / 3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(2.0f / 4.0f, 2.0f / 3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(2.0f / 4.0f, 1.0f / 3.0f), QVector3D(-1.0, 0.0, 0.0)));

    // Сверху
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(2.0f / 4.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(2.0f / 4.0f, 2.0f / 3.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0f / 4.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f / 4.0f, 2.0f / 3.0f), QVector3D(0.0, -1.0, 0.0)));

    // Спереди
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(2.0f / 4.0f, 2.0f / 3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(2.0f / 4.0f, 1.0f / 3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f / 4.0f, 2.0f / 3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f / 4.0f, 1.0f / 3.0f), QVector3D(0.0, 0.0, 1.0)));

    // Слева
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 2.0f / 3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f / 4.0f, 2.0f / 3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 1.0f / 3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f / 4.0f, 1.0f / 3.0f), QVector3D(1.0, 0.0, 0.0)));

    // Снизу
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0f / 4.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f / 4.0f, 1.0f / 3.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(2.0f / 4.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(2.0f / 4.0f, 1.0f / 3.0f), QVector3D(0.0, 1.0, 0.0)));

    QVector<GLuint> indexes;
    for ( int i = 0; i < 24; i += 4 ) {

        indexes.append ( i + 0 );
        indexes.append ( i + 2 );
        indexes.append ( i + 1 );

        indexes.append ( i + 2 );
        indexes.append ( i + 3 );
        indexes.append ( i + 1 );
    }

    __cube = new SimpleObject3d_v1( vertexes, indexes, texture );
}

SkyBoxOneCubeTexture::~SkyBoxOneCubeTexture()
{
    if ( __cube ) {
        delete __cube;
    }
}

void SkyBoxOneCubeTexture::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    __cube->draw( program, functions );
}
