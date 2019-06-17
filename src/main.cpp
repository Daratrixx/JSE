#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Qt-generated code
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // User-written code, to initialize the data context
    w.LoadFile();
    w.DisplaySaveData();

    // Qt-generated code
    return a.exec();
}
