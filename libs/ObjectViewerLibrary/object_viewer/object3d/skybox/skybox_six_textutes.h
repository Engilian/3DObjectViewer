#ifndef SKYBOX_SIX_TEXTUTES_H
#define SKYBOX_SIX_TEXTUTES_H

#include "i_skybox.h"

class SkyBoxSixTextutes : public ISkyBox
{
public:
    SkyBoxSixTextutes( float size = 150.0f );
    SkyBoxSixTextutes( float size, QList<QImage> textures );
    ~SkyBoxSixTextutes();
public:

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

private:

    void __init( float size, QList<QImage> textures );

private:

    QList<SimpleObject3d *> __planes;

};


#endif // SKYBOX_SIX_TEXTUTES_H
