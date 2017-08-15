#ifndef TEXTURE_CREATOR_H
#define TEXTURE_CREATOR_H

#include <QOpenGLTexture>
#include <QHash>
#include <memory>

using GlTexturePtr  = std::shared_ptr<QOpenGLTexture>;
using GlTextureWPtr = std::weak_ptr<QOpenGLTexture>;

///
/// \brief Загрузчик текстур для простого 3d объекта
///
class TextureCreatorSimpleObject3d
{
public:

    ///
    /// \brief Метод создания текстуры
    /// \param path путь к текстуре
    /// \return указатель на текстуру
    ///
    static GlTexturePtr createTexture( const QString &path );

private:

    ///
    /// \brief Метод загрузки текстуры
    /// \param path путь к текстуре
    /// \return текстура
    ///
    static GlTexturePtr loadTexture( const QString path );

private:

    ///
    /// \brief Список загруженных текстур
    ///
    static QHash<QString, GlTextureWPtr>        __textures;

protected:
    TextureCreatorSimpleObject3d() = delete;
};

#endif // TEXTURE_CREATOR_H
