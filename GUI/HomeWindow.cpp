#include "HomeWindow.h"
#include "ui_HomeWindow.h"

HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    QFont font("Calibri", 15);
    font.setBold(true);
    ui->treeWidget->setFont(font);

    ui->addSubWidget->hide();

    ui->DE_deadlineSub->setDate(QDate::currentDate());
    ui->DE_deadlineTask->setDate(QDate::currentDate());
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->addSubWidget->show();
    ui->LB_taskTitle->setText("Title: "+ item->text(0));

}

