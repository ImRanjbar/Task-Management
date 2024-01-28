
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../FileManager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(FileManager* file = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setPlaceHolders();

private slots:
    void on_PB_login_signUp_clicked();

    void on_PB_signUp_Login_clicked();

    void on_PB_login_clicked();

    void on_PB_signUp_clicked();

private:
    Ui::MainWindow *ui;
    FileManager* m_file;
};

#endif // MAINWINDOW_H
