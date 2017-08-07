#include "main_window.h"
#include <QApplication>
#include <object_viewer_info.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ObjectViewerInfo::setDefaultSurfaceFormat ();

    a.setApplicationDisplayName ( "ObjectViewer" );

    MainWindow w;
    w.show();

    return a.exec();
}
