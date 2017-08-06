#include "example_cube_3d.h"
#include <QImage>

ExampleCube3d::ExampleCube3d(float width): Cube3d( width, QImage( ":/example/test_brick.jpg" ) )
{
    this->setName( "Sample cube" );
}

ExampleCube3d::~ExampleCube3d()
{
//    Cube3d::~Cube3d();
}
