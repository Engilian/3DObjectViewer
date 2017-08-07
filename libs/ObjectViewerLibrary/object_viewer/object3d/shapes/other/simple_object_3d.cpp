#include "simple_object_3d.h"

SimpleObject3d::SimpleObject3d(): IObject3D(),
    __indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}
SimpleObject3d::SimpleObject3d(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture):
    IObject3D(),
    __indexBuffer(QOpenGLBuffer::IndexBuffer), __texture(0)
{
    init(vertData, indexes, texture);
}

SimpleObject3d::~SimpleObject3d()
{

    // Удаляем буфер вершин
    if ( __vertexBuffer.isCreated() ) {

        __vertexBuffer.destroy();
    }

    // Удаляем буфер индексов
    if ( __indexBuffer.isCreated() ) {

        __indexBuffer.destroy();
    }

    // Удаляем тектуру
    if ( __texture ) {

        if ( __texture->isCreated() ) {

            __texture->destroy();
        }

        delete __texture;
    }

}

void SimpleObject3d::init(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture)
{
    // Если буфер был создан очищаем
    if ( __vertexBuffer.isCreated() ) {
        __vertexBuffer.destroy();
    }

    // Если буфер был создан очищаем
    if ( __indexBuffer.isCreated() ) {
        __indexBuffer.destroy();
    }

    if (__texture != 0) {
        if ( __texture->isCreated())
        {
            delete __texture;
            __texture = 0;
        }
    }

    __vertexBuffer.create();
    __vertexBuffer.bind();
    __vertexBuffer.allocate(vertData.constData(), vertData.size() * sizeof(VertexData));
    __vertexBuffer.release();


    __indexBuffer.create();
    __indexBuffer.bind();
    __indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    __indexBuffer.release();

    __texture = new QOpenGLTexture( texture.mirrored() );


    __texture->setMinificationFilter(QOpenGLTexture::Nearest);
    __texture->setMagnificationFilter(QOpenGLTexture::Linear);
    __texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SimpleObject3d::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    (void)functions;

    if (!__vertexBuffer.isCreated() || !__indexBuffer.isCreated())
        return;

    QMatrix4x4 modelMatrix = createModelMatrix();

    __texture->bind(0);
    program->setUniformValue ( "u_modelMatrix", modelMatrix );
    program->setUniformValue ( "v_texcoord", 0 );

    __vertexBuffer.bind();

    int offset = 0;

    int vertLoc = program->attributeLocation ( "a_position" );
    program->enableAttributeArray ( vertLoc );
    program->setAttributeBuffer ( vertLoc, GL_FLOAT, offset, 3, sizeof( VertexData ) );

    offset += sizeof( QVector3D );

    int textLoc = program->attributeLocation ( "a_texcoord" );
    program->enableAttributeArray ( textLoc );
    program->setAttributeBuffer ( textLoc, GL_FLOAT, offset, 2, sizeof( VertexData ) );

    offset += sizeof( QVector2D );

    int normLoc = program->attributeLocation ( "a_normal" );
    program->enableAttributeArray ( normLoc );
    program->setAttributeBuffer ( normLoc, GL_FLOAT, offset, 3, sizeof( VertexData ) );

    __indexBuffer.bind ();
    glDrawElements ( GL_TRIANGLES, __indexBuffer.size (), GL_UNSIGNED_INT, 0 );

    __vertexBuffer.release();
    __indexBuffer.release();
    __texture->release();

}
