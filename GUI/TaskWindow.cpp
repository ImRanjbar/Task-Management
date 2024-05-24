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
    ui->LE_title->setText(item->text(0));
    ui->TE_description->setPlainText(item->text(1));
    QDate deadline = QDate::fromString(item->text(2).trimmed(), "d/M/yyyy");
    ui->DE_deadline->setDate(deadline);
}

TaskWindow::~TaskWindow()
{
    delete ui;
}

Date TaskWindow::qDateToDate(QDate &qDate)
{
    int day = qDate.day();
    int month = qDate.month();
    int year = qDate.year();

    return Date(day, month, year);
}

MyBinaryTree<Task>::Position TaskWindow::findTask()
{
    std::string title = m_item->text(0).toStdString();
    std::string description = m_item->text(1).toStdString();
    QDate qDate = QDate::fromString(m_item->text(2), "d/M/yyyy");
    Date deadline = qDateToDate(qDate);

    Task desiredTask(title, description, deadline);
    MyBinaryTree<Task>::Position posTask = m_file->user().taskManagement().tasks().editElement(desiredTask);
    return posTask;
}

bool TaskWindow::isTask()
{
    MyBinaryTree<Task>::Position pos = findTask();
    if (pos.isNull())
        return false;
    else
        return true;
}

void TaskWindow::edit(const Action &action)
{
    std::string title = ui->LE_title->text().toStdString();
    std::string description = ui->TE_description->toPlainText().toStdString();
    QDate qDate = ui->DE_deadline->date();
    Date deadline = qDateToDate(qDate);


    MyBinaryTree<Task>::Position posTask = findTask();

    if (posTask.isNull()){
        return;
    }
    else {

        Task copyTask = *posTask;
        Task& realTask = *posTask;

        copyTask.setTitle(title);
        copyTask.setDescription(description);
        copyTask.setDeadline(deadline);

        m_file->user().taskManagement().tasks().remove(realTask);
        m_file->user().taskManagement().tasks().insert(copyTask);
    }
}

void TaskWindow::on_PB_edit_clicked()
{
    if (isTask())
        edit(Action::Task);
    else
        edit(Action::SubTask);

    this->close();
}

