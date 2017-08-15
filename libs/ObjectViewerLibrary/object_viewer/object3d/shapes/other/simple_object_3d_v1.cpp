#include "simple_object_3d_v1.h"

SimpleObject3d_v1::SimpleObject3d_v1(): IObject3D(),
    __indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}
SimpleObject3d_v1::SimpleObject3d_v1(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QString &texture):
    IObject3D(),
    __indexBuffer(QOpenGLBuffer::IndexBuffer), __texture(0)
{
    init(vertData, indexes, texture);
}

SimpleObject3d_v1::~SimpleObject3d_v1()
{

    // Удаляем буфер вершин
    if ( __vertexBuffer.isCreated() ) {

        __vertexBuffer.destroy();
    }

    // Удаляем буфер индексов
    if ( __indexBuffer.isCreated() ) {

        __indexBuffer.destroy();
    }


    qDebug() << "deleted: " << name ();
}

void SimpleObject3d_v1::init(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QString &texture)
{
    // Если буфер был создан очищаем
    if ( __vertexBuffer.isCreated() ) {
        __vertexBuffer.destroy();
    }

    // Если буфер был создан очищаем
    if ( __indexBuffer.isCreated() ) {
        __indexBuffer.destroy();
    }

    __vertexBuffer.create();
    __vertexBuffer.bind();
    __vertexBuffer.allocate(vertData.constData(), vertData.size() * sizeof(VertexData));
    __vertexBuffer.release();


    __indexBuffer.create();
    __indexBuffer.bind();
    __indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    __indexBuffer.release();

    __texture = TextureCreatorSimpleObject3d::createTexture( texture );


    __texture.get()->setMinificationFilter(QOpenGLTexture::Nearest);
    __texture.get()->setMagnificationFilter(QOpenGLTexture::Linear);
    __texture.get()->setWrapMode(QOpenGLTexture::Repeat);
}

void SimpleObject3d_v1::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    (void)functions;

    if (!__vertexBuffer.isCreated() || !__indexBuffer.isCreated())
        return;

    QMatrix4x4 modelMatrix = createModelMatrix();

    __texture.get()->bind(0);
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
    __texture.get()->release();

}
