#ifndef SAMPLE_CUBE_3D_H
#define SAMPLE_CUBE_3D_H

#include "cube_3d.h"

///
/// \brief Пример куба
///
class ExampleCube3d : public Cube3d
{
public:
    ///
    /// \brief Конструктор
    /// \param width размер
    ///
    ExampleCube3d( float width = 1.0f );
    ~ExampleCube3d();
};

#endif // SAMPLE_CUBE_3D_H
