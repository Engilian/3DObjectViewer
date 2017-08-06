#include "triangleobject3d.h"

TriangleObject3D::TriangleObject3D(): __texture(0)
{

}

TriangleObject3D::~TriangleObject3D()
{
    while ( !__triangles.isEmpty() ) {
        delete __triangles.takeFirst();
    }

    if ( __texture ) {

        if ( __texture->isCreated() ) {
            __texture->destroy();
        }

        delete __texture;
    }
}

void TriangleObject3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    (void)functions;

    if ( __triangles.isEmpty() ) {
        return;
    }

    QMatrix4x4 modelMatrix = createModelMatrix();

    if ( __texture ) {

        __texture->bind(0);
        program->setUniformValue ( "u_modelMatrix", modelMatrix );
        program->setUniformValue ( "v_texcoord", 0 );
    }


    for ( TriangleBuffer *triangle: __triangles ) {

        triangle->draw( program, functions );
    }

    if ( __texture ) {

        __texture->release();
    }
}

void TriangleObject3D::initTexture(const QImage &texture)
{
    if (__texture != 0) {
        if ( __texture->isCreated())
        {
            delete __texture;
            __texture = 0;
        }
    }

    __texture = new QOpenGLTexture( texture.mirrored() );
    __texture->setMinificationFilter(QOpenGLTexture::Nearest);
    __texture->setMagnificationFilter(QOpenGLTexture::Linear);
    __texture->setWrapMode(QOpenGLTexture::Repeat);
}

void TriangleObject3D::addTriangle(const QVector<VertexData> &vertData)
{
    if ( vertData.size() < 3 ) {
        qDebug() << "ignore";
        return;
    }

    __triangles << new TriangleBuffer( vertData );
}

int TriangleObject3D::triangleCount() const
{
    return __triangles.count();
}

TriangleObject3D::TriangleBuffer::TriangleBuffer(): indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

TriangleObject3D::TriangleBuffer::TriangleBuffer(const QVector<VertexData> &vertData): indexBuffer(QOpenGLBuffer::IndexBuffer)
{

    init( vertData );
}

TriangleObject3D::TriangleBuffer::~TriangleBuffer()
{
    // Если буфер был создан очищаем
    if ( vertexBuffer.isCreated() ) {
        vertexBuffer.destroy();
    }

    // Если буфер был создан очищаем
    if ( indexBuffer.isCreated() ) {
        indexBuffer.destroy();
    }
}

void TriangleObject3D::TriangleBuffer::init(const QVector<VertexData> &vertData)
{
    static const QVector<GLuint> indexes = { 0, 1, 2 };

    // Если буфер был создан очищаем
    if ( vertexBuffer.isCreated() ) {
        vertexBuffer.destroy();
    }

    // Если буфер был создан очищаем
    if ( indexBuffer.isCreated() ) {
        indexBuffer.destroy();
    }

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vertData.constData(), vertData.size() * sizeof(VertexData));
    vertexBuffer.release();


    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    indexBuffer.release();
}

void TriangleObject3D::TriangleBuffer::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    (void)functions;

    vertexBuffer.bind();

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

    indexBuffer.bind ();
    glDrawElements ( GL_TRIANGLES, indexBuffer.size (), GL_UNSIGNED_INT, 0 );

    vertexBuffer.release();
    indexBuffer.release();
}
