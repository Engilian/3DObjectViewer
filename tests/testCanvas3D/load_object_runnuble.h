#ifndef LOAD_OBJECT_RUNNUBLE_H
#define LOAD_OBJECT_RUNNUBLE_H

#include <QRunnable>
#include "main_window.h"

class LoadObjectRunnuble: public QRunnable
{
public:
    LoadObjectRunnuble( MainWindow *mainwindow );
    ~LoadObjectRunnuble();
protected:

    void run();

private:

    MainWindow *mainwindow;
};

#endif // LOAD_OBJECT_RUNNUBLE_H
