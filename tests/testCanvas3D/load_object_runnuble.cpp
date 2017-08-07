#include "load_object_runnuble.h"
#include <thread>

LoadObjectRunnuble::LoadObjectRunnuble(MainWindow *mainwindow)
{
    this->mainwindow = mainwindow;
}

LoadObjectRunnuble::~LoadObjectRunnuble()
{

}

void LoadObjectRunnuble::run()
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 2500 ) );

    if ( mainwindow ) {

        mainwindow->initBelka ();
    }
}
