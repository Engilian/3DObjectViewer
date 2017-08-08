#ifndef SKB_LOADER_H
#define SKB_LOADER_H

#include "../../i_skybox.h"


///
/// \brief Загрузчик skybox для собственого формата
///
class SkbLoader
{
public:
    SkbLoader();
    ~SkbLoader();
public:

    ///
    /// \brief load
    /// \param pathToSkb
    ///
    ISkyBox *load( const QString pathToSkb );

protected:

    ///
    /// \brief Структура путей до файлов
    ///
    struct SkyBoxPathTexture {

        QString back;
        QString right;
        QString up;
        QString front;
        QString left;
        QString down;
    };
};

#endif // SKB_LOADER_H
