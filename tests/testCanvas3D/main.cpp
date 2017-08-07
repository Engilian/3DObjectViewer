#include "main_window.h"
#include <QApplication>

#include <object_viewer_info.h>

#include <object_viewer/object3d/object_loader/object_loader_triangle_object3d.h>

int main(int argc, char *argv[])
{
    ObjectViewerInfo::setDefaultSurfaceFormat( 16, 24 );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.init();

    return a.exec();
}
