#include "HomeWindow.h"
#include "ui_HomeWindow.h"
#include <QString>

HomeWindow::HomeWindow(FileManager* file, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    m_file = file;

    ui->setupUi(this);
    this->setWindowTitle("Home");

    connect(this, &QMainWindow::destroyed, this, &HomeWindow::windowClosed);


    ui->LB_welcome->setText("Welcome " + QString::fromStdString(m_file->user().getName()));

    QFont font("Calibri", 15);
    font.setBold(true);
    ui->treeWidget->setFont(font);

    ui->addSubWidget->hide();

    ui->DE_deadlineSub->setDate(QDate::currentDate());
    ui->DE_deadlineTask->setDate(QDate::currentDate());
}

HomeWindow::~HomeWindow()
{
    std::cerr << "HomeWindow destructure\n";
    delete ui;
}

void HomeWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->addSubWidget->show();
    ui->LB_taskTitle->setText("Title: "+ item->text(0));

}

void HomeWindow::on_PB_logout_clicked()
{
    this->windowClosed();
}

