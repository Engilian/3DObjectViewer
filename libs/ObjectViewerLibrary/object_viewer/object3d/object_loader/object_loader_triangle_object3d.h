#ifndef TRIANGLE_OBJECT_3D_LOADER_H
#define TRIANGLE_OBJECT_3D_LOADER_H

#include <QString>

#include "i_object_loader.h"

///
/// \brief Загрузчик obj файла в TriangleObject3D
///
class TriangleObject3dLoader : public IObjectLoader
{
public:
    TriangleObject3dLoader();
    ~TriangleObject3dLoader();
public:

    QList<IObject3D *> load( QString pathObj, QString pathMtl );

    QImage loadTetxture( QString pathMtl, QString nameMtl );

    QVector3D readVector3D ( const QString raw );
    QVector2D readVector2D ( const QString raw );

    QVector<VertexData> readPolygon( const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs );

    VertexData readVertexData( const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs );


};

#endif // TRIANGLE_OBJECT_3D_LOADER_H
