#include "TaskWindow.h"
#include "ui_TaskWindow.h"

TaskWindow::TaskWindow(FileManager* file, QTreeWidgetItem* item, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskWindow)
{
    m_item = item;
    m_file = file;

    connect(this, &QDialog::finished, this, &TaskWindow::dialogClosed);

    ui->setupUi(this);

    this->setWindowTitle("Edit Task");
    ui->LE_title->setText("jafar");
    ui->TE_description->setPlainText(item->text(1));
    QDate deadline = QDate::fromString(item->text(2).trimmed(), "d/M/yyyy");
    ui->DE_deadline->setDate(deadline);
}

TaskWindow::~TaskWindow()
{
    delete ui;
}
