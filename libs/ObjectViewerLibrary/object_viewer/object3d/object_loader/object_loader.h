#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

#include <QString>

#include "i_object_loader.h"

struct TriangleIndex {

    int vertexIndex;
    int normalIndex;
    int uvIndex;
};

struct Triangle {

    QVector<TriangleIndex> indexes;
};

class ObjectLoader : public IObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();
public:

    QList<IObject3D *> load( QString pathObj, QString pathMtl );

    QImage loadTetxture( QString pathMtl, QString nameMtl );

    QVector3D readVector3D ( const QString raw );
    QVector2D readVector2D ( const QString raw );

    QVector<VertexData> readPolygon( const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs );

    VertexData readVertexData( const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs );


};

#endif // OBJECT_LOADER_H
