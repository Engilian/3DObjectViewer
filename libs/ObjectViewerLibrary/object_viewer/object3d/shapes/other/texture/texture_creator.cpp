#include "texture_creator.h"
#include <QDebug>

QHash<QString, GlTextureWPtr>  TextureCreatorSimpleObject3d::__textures;

GlTexturePtr TextureCreatorSimpleObject3d::createTexture(const QString &path)
{
    if ( __textures.contains( path ) ) {

        GlTexturePtr ptr = __textures[ path ].lock();

        if ( ptr.get() ) {

            qDebug() << "Texture is already loaded: " << path;
            return ptr;
        }
        else {

            __textures.remove( path );
        }
    }

    return loadTexture( path );
}

GlTexturePtr TextureCreatorSimpleObject3d::loadTexture(const QString path)
{
    GlTexturePtr ptr ( new QOpenGLTexture( QImage( path ).mirrored() ) );
    __textures[ path ] = GlTextureWPtr( ptr );

    qDebug() << "Texture loaded: " << path;

    return ptr;
}
