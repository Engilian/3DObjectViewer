#ifndef SKYBOX_H
#define SKYBOX_H

#include "i_skybox.h"

///
/// \brief Реализация скайбокса для одной текстуры куба
///
class SkyBoxOneCubeTexture: public ISkyBox
{
public:
    SkyBoxOneCubeTexture(float width = 150.0f, QImage texture = QImage( ":/example/skybox_1file/test_skybox_one_cube_texture.jpg" ) );
    ~SkyBoxOneCubeTexture();
public:
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

private:

    SimpleObject3d  *__cube;

};

#endif // SKYBOX_H