#include "skb_loader.h"
#include "../../skybox_six_textutes.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDomDocument>


SkbLoader::SkbLoader()
{

}

SkbLoader::~SkbLoader()
{

}

ISkyBox *SkbLoader::load(const QString pathToSkb)
{
    QFile f( pathToSkb );

    if ( f.open ( QIODevice::ReadOnly ) ) {

        QDomDocument doc;
        QString error;
        int line, column;

        if ( doc.setContent( &f, true,&error, &line, &column ) ) {

            QFileInfo fileInfo( f );

            QDomElement skyboxElement = doc.firstChildElement ( "skybox" );

            if  ( !skyboxElement.isNull () ) {

                SkyBoxPathTexture paths;

                QDomNodeList childs = skyboxElement.elementsByTagName ( "img" );

                for ( int i = 0; i < childs.count (); ++i ) {

                    QDomElement img = childs.at ( i ).toElement ();

                    QString pos = img.attribute ( "pos" );
                    QString src = img.attribute ( "src" );

                    if  ( pos.compare ( "back" ) == 0 ) {

                        paths.back = src;
                    }
                    else if  ( pos.compare ( "right" ) == 0 ) {

                        paths.right = src;
                    }
                    else if  ( pos.compare ( "up" ) == 0 ) {

                        paths.up = src;
                    }
                    else if  ( pos.compare ( "front" ) == 0 ) {

                        paths.front = src;
                    }
                    else if  ( pos.compare ( "left" ) == 0 ) {

                        paths.left = src;
                    }
                    else if  ( pos.compare ( "down" ) == 0 ) {

                        paths.down = src;
                    }

                }

                QStringList pathsImages;
                pathsImages << paths.back   << paths.right
                            << paths.up     << paths.front
                            << paths.left   << paths.down;

                QList<QImage> textures;

                for ( const QString &path: pathsImages ) {

                    QString src = fileInfo.dir ().absoluteFilePath ( path );
                    textures << QImage( src );
                }

                return new SkyBoxSixTextutes( 1000.0f, textures );
            }

        }
        else {

            qDebug() << "Error parse file: " << line << ":" << column << error;
        }

    }

    return nullptr;
}
