
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "HomeWindow.h"


MainWindow::MainWindow(FileManager* file, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_file = file;

    ui->setupUi(this);
    ui->signUpWidget->hide();
}

MainWindow::~MainWindow()
{
    std::cerr << "MainWindow destructure\n";

    delete ui;
    delete m_file;
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

    std::string username = ui->LE_loginUser->text().trimmed().toStdString();
    std::string password = ui->LE_loginPass->text().trimmed().toStdString();

    m_file->user().setUsername(username);
    m_file->user().setPassword(password);

    if (m_file->searchUser() == FileManager::success){
        m_file->readUser();
        m_file->readData();
    }
    else {
        std::cerr << "pass or user incorrect\n";
        return;
    }

    HomeWindow* homeWindow = new HomeWindow(m_file, this);

    connect(homeWindow, &HomeWindow::windowClosed, this, &QCoreApplication::quit);

    close();
    homeWindow->show();
}

void MainWindow::on_PB_signUp_clicked()
{
    std::string name = ui->LE_name->text().toStdString();
    std::string lastname = ui->LE_lastname->text().trimmed().toStdString();
    std::string email = ui->LE_email->text().trimmed().toStdString();
    std::string username = ui->LE_username->text().trimmed().toStdString();
    std::string password = ui->LE_password->text().trimmed().toStdString();

    m_file->user().setName(name);
    m_file->user().setLastname(lastname);
    m_file->user().setEmail(email);
    m_file->user().setUsername(username);
    m_file->user().setPassword(password);

    if (m_file->searchUser() == FileManager::wrongUsername){
        m_file->addUser();
    }

    else {
        std::cerr << "Username already exists\n";
        return;
    }


    HomeWindow* homeWindow = new HomeWindow(m_file ,this);

    connect(homeWindow, &HomeWindow::windowClosed, this, &QCoreApplication::quit);

    close();
    homeWindow->show();
}

