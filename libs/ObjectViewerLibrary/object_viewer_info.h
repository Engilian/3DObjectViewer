#ifndef OBJECT_VIEWER_INFO_H
#define OBJECT_VIEWER_INFO_H

#include <QSurfaceFormat>

class ObjectViewerInfo
{

public:
    ObjectViewerInfo();

public:

    ///
    /// \brief Установка формата отрисовки
    /// \param samples количество семплов отрисовки
    /// \param depthBufferSize размер буфера глубины
    ///
    static void setDefaultSurfaceFormat(int samples = 16, int depthBufferSize = 24 );
};

#endif // OBJECT_VIEWER_INFO_H
