
#include "GUI/mainwindow.h"

#include <QApplication>
#include "FileManager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Task Management");
    w.show();
    return a.exec();
}
