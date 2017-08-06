#include "i_skybox.h"

ISkyBox::ISkyBox()
{

}

ISkyBox::~ISkyBox()
{

}

void ISkyBox::rotate(const QQuaternion &q)
{
    (void)q;
}

void ISkyBox::translate(const QVector3D &t)
{
    (void)t;
}

void ISkyBox::scale(const float scale)
{
    (void)scale;
}

void ISkyBox::setGlobalTransform(const QMatrix4x4 &m)
{
    (void)m;
}
