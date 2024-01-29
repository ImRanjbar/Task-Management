#include "HomeWindow.h"
#include "ui_HomeWindow.h"
#include "TaskWindow.h"

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
    populateTreeWidget();

    ui->addSubWidget->hide();

    ui->DE_deadlineSub->setDate(QDate::currentDate());
    ui->DE_deadlineTask->setDate(QDate::currentDate());
}

HomeWindow::~HomeWindow()
{
    std::cerr << "HomeWindow destructure\n";
    m_file->saveTasks();
    delete ui;
}

void HomeWindow::populateTreeWidget()
{
    ui->treeWidget->clear();

    std::list<Task> tasks = m_file->user().taskManagement().tasks().inOrderList();

    for (Task& task : tasks){
        QTreeWidgetItem* taskItem = new QTreeWidgetItem(ui->treeWidget);
        taskItem->setText(0, QString::fromStdString(task.getTitle()));
        taskItem->setText(1, QString::fromStdString(task.getDescription()));
        taskItem->setText(2, QString::fromStdString(task.getDeadline().toString()));

        std::vector<SubTask> subs = task.subTasks();
        for (SubTask& subTask : subs){
            QTreeWidgetItem* subTaskItem = new QTreeWidgetItem(taskItem);
            subTaskItem->setText(0, QString::fromStdString(subTask.getTitle()));
            subTaskItem->setText(1, QString::fromStdString(subTask.getDescription()));
            subTaskItem->setText(2, QString::fromStdString(subTask.getDeadline().toString()));
        }
    }

    ui->PB_done->setEnabled(false);
    ui->addSubWidget->hide();
}

bool HomeWindow::isTask(QTreeWidgetItem* item)
{
    if (item->parent()){
        return false;
    }
    else {
        return true;
    }
}

void HomeWindow::taskDone(const MyBinaryTree<Task>::Position& posTask)
{
    if ((*posTask).subTasks().empty()){
        m_file->user().taskManagement().tasks().remove(posTask);
    }
}

Date HomeWindow::qDateToDate(QDate &qDate)
{
    int day = qDate.day();
    int month = qDate.month();
    int year = qDate.year();

    return Date(day, month, year);
}

void HomeWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->addSubWidget->show();
    ui->LB_taskTitle->setText("Title: "+ item->text(0));

    ui->PB_done->setEnabled(true);
}

void HomeWindow::on_PB_logout_clicked()
{
    emit this->windowClosed();
}


void HomeWindow::on_PB_addTask_clicked()
{
    std::string title = ui->LE_titleTask->text().trimmed().toStdString();
    std::string description = ui->TE_desTask->toPlainText().trimmed().toStdString();
    QDate date = ui->DE_deadlineTask->date();
    Date deadline = qDateToDate(date);

    Task newTask(title, description, deadline);
    m_file->user().taskManagement().tasks().insert(newTask);

    populateTreeWidget();
}


void HomeWindow::on_PB_addSub_clicked()
{

    // get the position of the task in BinaryTree
    QTreeWidgetItem* selectedItem = ui->treeWidget->currentItem();

    std::string taskTitle = selectedItem->text(0).trimmed().toStdString();
    std::string taskDescription = selectedItem->text(1).trimmed().toStdString();
    QDate taskDate = QDate::fromString(selectedItem->text(2).trimmed(), "d/M/yyyy");
    Date taskDeadline = qDateToDate(taskDate);

    Task desiredTask(taskTitle, taskDescription, taskDeadline);
    MyBinaryTree<Task>::Position positionTask = m_file->user().taskManagement().tasks().editElement(desiredTask);

    Task& realTask = *positionTask;


    // add SubTask to realTask
    std::string title = ui->LE_titleSub->text().trimmed().toStdString();
    std::string description = ui->TE_desSub->toPlainText().trimmed().toStdString();
    QDate date = ui->DE_deadlineSub->date();
    Date deadline = qDateToDate(date);

    SubTask newSub(title, description, deadline);
    realTask.addSubTask(newSub);

    populateTreeWidget();
}

void HomeWindow::on_PB_done_clicked()
{

    QTreeWidgetItem* selectedItem = ui->treeWidget->currentItem();

    std::string title = selectedItem->text(0).trimmed().toStdString();
    std::string description = selectedItem->text(1).trimmed().toStdString();
    QDate date = QDate::fromString(selectedItem->text(2).trimmed(), "d/M/yyyy");
    Date deadline = qDateToDate(date);

    if (isTask(selectedItem)){
        Task desiredTask(title, description, deadline);

        m_file->user().taskManagement().tasks().remove(desiredTask);
    }
    else {
        QTreeWidgetItem* taskItem = ui->treeWidget->currentItem()->parent();

        std::string taskTitle = taskItem->text(0).toStdString();
        std::string taskDes = taskItem->text(1).toStdString();

        QDate taskDead = QDate::fromString(taskItem->text(2), "d/M/yyyy");
        int taskDay = taskDead.day();
        int taskMonth = taskDead.month();
        int taskYear = taskDead.year();
        Date taskDeadline(taskDay, taskMonth, taskYear);

        Task desiredTask(taskTitle, taskDes, taskDeadline);
        MyBinaryTree<Task>::Position positionTask = m_file->user().taskManagement().tasks().editElement(desiredTask);

        Task& realTask = *positionTask;
        SubTask desiredSub(title, description, deadline);

        realTask.removeSubTask(desiredSub);
        taskDone(positionTask);
    }

    populateTreeWidget();
}

void HomeWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    TaskWindow* taskWindow = new TaskWindow(m_file, item, this);
    connect(taskWindow, &TaskWindow::dialogClosed, this, &HomeWindow::onDialogClosed);

    taskWindow->setModal(true);
    taskWindow->show();
}

void HomeWindow::onDialogClosed()
{
    populateTreeWidget();
}

