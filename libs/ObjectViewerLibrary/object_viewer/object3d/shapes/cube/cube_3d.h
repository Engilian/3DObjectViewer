#ifndef CUBE_3D_H
#define CUBE_3D_H

#include "../other/simple_object_3d.h"

///
/// \brief Класс куба
///
class Cube3d : public SimpleObject3d
{
public:
    ///
    /// \brief Конструктор
    /// \param width размер куба
    /// \param texture текстура ( одна текстура на все грани )
    ///
    Cube3d( float width, QImage texture );
    virtual ~Cube3d();
public:
};

#endif // CUBE_3D_H
