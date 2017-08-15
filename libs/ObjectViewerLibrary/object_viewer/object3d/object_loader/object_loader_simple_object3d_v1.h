#ifndef SIMPLE_OBJECT_3D_LOADER_V1_H
#define SIMPLE_OBJECT_3D_LOADER_V1_H

#include <QString>

#include "i_object_loader.h"

///
/// \brief Загрузчик obj файла в SimpleObject3D ( обладает более быстрой отрисовкой )
///
class SimpleObject3dLoader_v1 : public IObjectLoader
{
public:
    SimpleObject3dLoader_v1();
    ~SimpleObject3dLoader_v1();
public:

    QList<IObject3D *> load( QString pathObj, QString pathMtl );

public:

    QString loadTexture( QString pathMtl, QString nameMtl );

    QString loadTexture( QString pathMtl, QString pathTexture, bool *ok );

    QVector3D readVector3D ( const QString raw );
    QVector2D readVector2D ( const QString raw );

    QVector<VertexData> readPolygon( const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs );

    VertexData readVertexData( const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs );


};

#endif // SIMPLE_OBJECT_3D_LOADER_V1_H
