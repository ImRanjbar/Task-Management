
#include "GUI/mainwindow.h"

#include <QApplication>
#include "FileManager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User* user = new User;
    FileManager* file = new FileManager(*user);

    MainWindow w(file);
    w.setWindowTitle("Task Management");
    w.show();
    return a.exec();
}
