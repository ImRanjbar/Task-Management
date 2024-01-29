
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

    hideErrors(Action::Login);
    hideErrors(Action::SignUp);
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

void MainWindow::hideErrors(const MainWindow::Action& action)
{
    switch (action){
    case MainWindow::Action::Login:
        ui->LB_errorUsername->hide();
        ui->LB_errorPassword->hide();
        break;

    case MainWindow::Action::SignUp:
        ui->LB_errorName->hide();
        ui->LB_errorLastname->hide();
        ui->LB_errorEmail->hide();
        ui->LB_errorUsernameSnUp->hide();
        ui->LB_errorPassSnUp->hide();
        break;

    default:
        break;
    }

}

bool MainWindow::checkInputValidity(const Action& action)
{
    switch (action) {
    case Action::Login:
    {
        QString qUsername = ui->LE_loginUser->text().trimmed();
        QString qPassword = ui->LE_loginPass->text().trimmed();

        bool isValid = true;

        if (qUsername.isEmpty()) {
            showError(ui->LB_errorUsername, "This field is required");
            isValid = false;
        }

        if (qPassword.isEmpty()) {
            showError(ui->LB_errorPassword, "This field is required");
            isValid = false;
        }

        if (!isValid)
            return isValid;

        std::string username = qUsername.toStdString();
        std::string password = qPassword.toStdString();
        FileManager::status status = FileManager::searchUser(username, password);

        if (status == FileManager::status::wrongUsername) {
            showError(ui->LB_errorUsername, "This username doesn't exist");
            return false;
        }
        else if (status == FileManager::status::wrongPass) {
            showError(ui->LB_errorPassword, "Incorrect password");
            return false;
        }

        return true;
    }

    case Action::SignUp:
    {

        if (!checkEmptyInput(Action::SignUp))
            return false;

        std::string username = ui->LE_username->text().trimmed().toStdString();
        FileManager::status status = FileManager::searchUser(username);

        if ((status == FileManager::wrongPass) || (status == FileManager::status::success)) {
            showError(ui->LB_errorUsernameSnUp, "This username already exists");
            return false;
        }

    }

    default:
        break;
    }

    return false;
}

bool MainWindow::checkEmptyInput(const Action &action)
{
    switch(action){

    case Action::SignUp:
    {
        QString qName = ui->LE_name->text().trimmed();
        QString qLastName = ui->LE_lastname->text().trimmed();
        QString qEmail = ui->LE_email->text().trimmed();
        QString qUsername = ui->LE_username->text().trimmed();
        QString qPass = ui->LE_password->text().trimmed();

        bool isEmpty = false;

        if (qName.isEmpty()){
            showError(ui->LB_errorName, "This field is required");
            isEmpty = true;
        }
        if (qLastName.isEmpty()){
            showError(ui->LB_errorLastname, "This field is required");
            isEmpty = true;
        }
        if (qEmail.isEmpty()){
            showError(ui->LB_errorEmail, "This field is required");
            isEmpty = true;
        }
        if (qUsername.isEmpty()){
            showError(ui->LB_errorUsernameSnUp, "This field is required");
            isEmpty = true;
        }
        if (qPass.isEmpty()){
            showError(ui->LB_errorPassSnUp, "This field is required");
            isEmpty = true;
        }

        return !isEmpty;
    }

    default:
        return true;
    }
}


void MainWindow::showError(QLabel* labelError, QString error)
{
    labelError->setText(error);
    labelError->show();
}

void MainWindow::readUserData()
{
    std::string username = ui->LE_loginUser->text().trimmed().toStdString();
    std::string password = ui->LE_loginPass->text().trimmed().toStdString();

    m_file->user().setUsername(username);
    m_file->user().setPassword(password);

    m_file->readUser();
    m_file->readData();

}

void MainWindow::signUpUser()
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


    m_file->addUser();
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
    hideErrors(Action::Login);
    if (checkInputValidity(Action::Login))
        readUserData();
    else
        return;

    HomeWindow* homeWindow = new HomeWindow(m_file, this);
    connect(homeWindow, &HomeWindow::windowClosed, this, &QCoreApplication::quit);

    close();
    homeWindow->show();
}

void MainWindow::on_PB_signUp_clicked()
{
    hideErrors(Action::SignUp);
    if (checkInputValidity(Action::SignUp))
        signUpUser();
    else
        return;

    HomeWindow* homeWindow = new HomeWindow(m_file ,this);
    connect(homeWindow, &HomeWindow::windowClosed, this, &QCoreApplication::quit);

    close();
    homeWindow->show();
}

