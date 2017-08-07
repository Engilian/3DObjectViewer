#include "object_loader_triangle_object3d.h"

#include <QFile>
#include "../shapes/triangle_object/triangleobject3d.h"

TriangleObject3dLoader::TriangleObject3dLoader()
{

}

TriangleObject3dLoader::~TriangleObject3dLoader()
{

}

QList<IObject3D *> TriangleObject3dLoader::load(QString pathObj, QString pathMtl)
{
    QList<IObject3D *> result;

    QFile f( pathObj );

    if  ( !f.exists() ) {

        return result;
    }

    if ( !f.open( QIODevice::ReadOnly ) ) {

        qDebug() << "error open obj file: " << f.errorString();
        return result;
    }

    TriangleObject3D *obj = nullptr;
    QString lastMaterial;

    QList<QVector3D>    points;
    QList<QVector3D>    normals;
    QList<QVector2D>    uv;


    while ( !f.atEnd() ) {

        QString line = QString::fromUtf8( f.readLine() );

        if ( line[0] == '#' ) {
            continue;
        }
        else if ( line[0] == 'u' ) {

            if ( line.indexOf( "usemtl" ) != -1 ) {

                lastMaterial = line.trimmed().split( ' ' ).last();

                if ( obj != nullptr ) {

                    QImage texture = loadTetxture( pathMtl, lastMaterial );
                    obj->initTexture( texture );
                }
            }
        }
        else if ( line[0] == 'o' ) {

            if ( obj != nullptr ) {

                qDebug() << "loaded: " << obj->name() << obj->triangleCount() ;
            }

            const QString name = line.trimmed().split( ' ' ).last();
            obj = new TriangleObject3D();
            obj->setName( name );
            result << obj;
        }

        // Если заголовок объекта еще не найден
        if ( obj != nullptr ) {

            if ( line.length() < 2 ) {
                continue;
            }

            // Координаты нормалей
            if ( line[0] == 'v' && line[1] == 'n' ) {

                normals << readVector3D( line );
            }
            // Координаты текстуры
            else if ( line[0] == 'v' && line[1] == 't' ) {

                uv << readVector2D( line );
            }
            // Точки
            else if ( line[0] == 'v' ) {

                points << readVector3D( line );
            }
            // Грани
            else if ( line[0] == 'f' ) {

                QVector<VertexData> temp = readPolygon( line, &points, &normals, &uv );
                obj->addTriangle( temp );
            }

        }
    }

    if ( obj != nullptr ) {

        qDebug() << "loaded: " << obj->name() << obj->triangleCount() ;
    }


    if ( f.isOpen() ) {
        f.close();
    }

    return result;
}

QImage TriangleObject3dLoader::loadTetxture(QString pathMtl, QString nameMtl)
{
    QImage image;

    QFile f( pathMtl );

    //    if ( f.exists() ) {

    if ( f.open( QIODevice::ReadOnly ) ) {

        bool isFindMaterial = false;

        while ( !f.atEnd() ) {

            QString line = QString::fromUtf8( f.readLine(  ) );

            if ( isFindMaterial ) {

                if ( line.indexOf( "map_Kd" ) == 0 ) {

                    QString path = line.mid( 6 ).trimmed();
                    image.load( path );
                    qDebug() << "find " << path;
                    f.close();
                    return image;
                }

            }
            else {

                if ( line.indexOf( "newmtl" ) == 0 ) {

                    QString name = line.mid( 6 ).trimmed();

                    if ( nameMtl.compare( name ) == 0 ) {

//                        qDebug() << "Найден материал " << name;
                        isFindMaterial = true;
                    }
                }
            }
        }

        f.close();
    }
    else {
        qDebug() << "Не удалось открыть файл материала: " << pathMtl << f.errorString();
    }
    //    }

    qDebug() << "Текстура не найдена, будет использована по умолчанию";
    image.load( ":/example/test_brick.jpg" );
    return image;//QImage( ":/example/test_brick.jpg" );
}

QVector3D TriangleObject3dLoader::readVector3D(const QString raw)
{
    QVector3D vector;

    QStringList list = raw.trimmed().split( ' ' );
    list.removeFirst();

    if ( !list.isEmpty() ) {
        QString value = list.takeFirst();
        vector.setX( value.toDouble() );
    }

    if ( !list.isEmpty() ) {
        QString value = list.takeFirst();
        vector.setY( value.toDouble() );
    }

    if ( !list.isEmpty() ) {
        QString value = list.takeFirst();
        vector.setZ( value.toDouble() );
    }

    return vector;
}

QVector2D TriangleObject3dLoader::readVector2D(const QString raw)
{
    QVector2D vector;

    QStringList list = raw.trimmed().split( ' ' );
    list.removeFirst();

    if ( !list.isEmpty() ) {
        QString value = list.takeFirst();
        vector.setX( value.toDouble() );
    }

    if ( !list.isEmpty() ) {
        QString value = list.takeFirst();
        vector.setY( value.toDouble() );
    }

    return vector;
}

QVector<VertexData> TriangleObject3dLoader::readPolygon(const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs)
{
    QVector<VertexData> result;

    QStringList list = raw.trimmed().split( ' ' );
    list.removeFirst();

    for ( const QString &vertex: list ) {

        result << readVertexData( vertex.trimmed(), points, normas, uvs );
    }

    return result;
}

VertexData TriangleObject3dLoader::readVertexData(const QString raw, QList<QVector3D> *points, QList<QVector3D> *normas, QList<QVector2D> *uvs)
{
    QStringList list = raw.split( '/' );
    VertexData vertex;

    if ( !list.isEmpty() ) {
        QString value = list.takeFirst();
        int index = value.toInt() - 1;

        if  ( points->size() > index && index >= 0 ) {

            vertex.position = points->at(  index );
        }
    }

    if ( !list.isEmpty() ) {

        QString value = list.takeFirst();
        int index = value.toInt() - 1;

        if  ( uvs->size() > index && index >= 0 ) {

            vertex.texture = uvs->at( index );
        }
    }

    if ( !list.isEmpty() ) {

        QString value = list.takeFirst();
        int index = value.toInt() - 1;

        if  ( normas->size() > index && index >= 0 ) {

            vertex.normal = normas->at( index );
        }
    }

    return vertex;
}
