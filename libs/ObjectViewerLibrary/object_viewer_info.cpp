#include "object_viewer_info.h"


ObjectViewerInfo::ObjectViewerInfo()
{
}

void ObjectViewerInfo::setDefaultSurfaceFormat(int samples, int depthBufferSize)
{
    QSurfaceFormat format;
    format.setSamples(  samples );
    format.setDepthBufferSize( depthBufferSize );
    QSurfaceFormat::setDefaultFormat( format );
}
