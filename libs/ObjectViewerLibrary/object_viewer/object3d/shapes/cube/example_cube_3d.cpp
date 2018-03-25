#include "example_cube_3d.h"

#include <QDir>
#include <QCoreApplication>
#include <QImage>

ExampleCube3d::ExampleCube3d(float width):
    Cube3d( width, QImage(
                QDir::fromNativeSeparators(
                    QCoreApplication::applicationDirPath() +
                    "res/textures/test_brick.jpg" ) ) )
{
    this->setName( "Sample cube" );
}

ExampleCube3d::~ExampleCube3d()
{

}
