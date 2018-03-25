#ifndef SKYBOX_H
#define SKYBOX_H

#include "i_skybox.h"

///
/// \brief Реализация скайбокса для одной текстуры куба
///
class SkyBoxOneCubeTexture: public ISkyBox
{
public:
    SkyBoxOneCubeTexture(float width, QString texture );
    ~SkyBoxOneCubeTexture();
public:
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

private:

    SimpleObject3d_v1  *__cube;

};

#endif // SKYBOX_H
