#ifndef I_OBJECT_LOADER_H
#define I_OBJECT_LOADER_H

#include "../i_object_3d.h"

///
/// \brief Интерфейс загрузчика obj файлов
///
class IObjectLoader
{
protected:
    IObjectLoader();
public:
    virtual ~IObjectLoader();
public:

    ///
    /// \brief Загрузить
    /// \param path путь к файлу
    /// \return список загруженных фалов
    ///
    virtual QList<IObject3D *> load( QString pathObj, QString pathMtl ) = 0;

};

#endif // I_OBJECT_LOADER_H
