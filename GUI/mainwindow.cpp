
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "HomeWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->signUpWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPlaceHolders()
{
    ui->LE_name->setPlaceholderText("Name");
    ui->LE_lastname->setPlaceholderText("Lastname");
    ui->LE_email->setPlaceholderText("Email Address");
    ui->LE_username->setPlaceholderText("Username");
    ui->LE_password->setPlaceholderText("Password");
}

void MainWindow::on_PB_login_signUp_clicked()
{
    ui->signUpWidget->show();
    setPlaceHolders();
    ui->loginWidget->hide();
}

void MainWindow::on_PB_signUp_Login_clicked()
{
    ui->loginWidget->show();
    ui->signUpWidget->hide();
}

void MainWindow::on_PB_login_clicked()
{
    HomeWindow* homeWindow = new HomeWindow(this);
    homeWindow->setWindowTitle("Home");
    close();
    homeWindow->show();
}
