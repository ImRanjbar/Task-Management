#include "HomeWindow.h"
#include "ui_HomeWindow.h"
#include "TaskWindow.h"

#include <QString>


HomeWindow::HomeWindow(FileManager* file, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    m_file = file;

    this->setWindowTitle("Home");
    ui->setupUi(this);

    ui->LB_welcome->setText("Welcome " + QString::fromStdString(m_file->user().getName()));

    QFont font("Calibri", 15);
    ui->treeWidget->setFont(font);
    ui->treeWidget->setColumnWidth(0,130);
    ui->treeWidget->setColumnWidth(1,220);
    ui->treeWidget->setColumnWidth(2, 90);
    populateTreeWidget();

    ui->addSubWidget->hide();
    refreshWidgets(Action::Task);
}

HomeWindow::~HomeWindow()
{
    std::cerr << "HomeWindow destructure\n";
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

    refreshWidgets(Action::Task);
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

void HomeWindow::hideErrors(const Action &action)
{
    switch (action){
    case Action::Task:
        ui->LB_errorTaskTitle->hide();
        break;

    case Action::SubTask:
        ui->LB_errorSubTitle->hide();
        break;
    }
}

void HomeWindow::showError(QLabel *labelError, QString error)
{
    labelError->setText(error);
    labelError->show();
}

void HomeWindow::refreshWidgets(const Action &action)
{
    switch (action){
    case Action::Task:
        ui->LE_titleTask->clear();
        ui->LB_errorTaskTitle->hide();
        ui->DE_deadlineTask->setDate(QDate::currentDate());
        ui->TE_desTask->clear();
        break;

    case Action::SubTask:
        ui->LE_titleSub->clear();
        ui->LB_errorSubTitle->hide();
        ui->DE_deadlineSub->setDate(QDate::currentDate());
        ui->TE_desSub->clear();
        break;
    }
}

bool HomeWindow::checkInputValidity(const Action &action)
{
    switch (action) {
    case Action::Task:
    {
        QString title = ui->LE_titleTask->text().trimmed();
        if (title.isEmpty()){
            showError(ui->LB_errorTaskTitle, "This field is required");
            return false;
        }
    }
        break;

    case Action::SubTask:
    {
        QString subTitle = ui->LE_titleSub->text().trimmed();
        if (subTitle.isEmpty()){
            showError(ui->LB_errorSubTitle, "This field is required");
            return false;
        }
    }
        break;
    }

    return true;
}

void HomeWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->addSubWidget->hide();
    ui->PB_done->setEnabled(true);

    std::string title = item->text(0).toStdString();
    std::string des = item->text(1).toStdString();
    QDate qDate = QDate::fromString(item->text(2), "d/M/yyyy");
    Date deadline = qDateToDate(qDate);

    Task currentTask(title, des, deadline);
    if (!m_file->user().taskManagement().tasks().contains(currentTask))
        return;

    refreshWidgets(Action::SubTask);
    ui->LB_taskTitle->setText("Task Title: "+ item->text(0));
    ui->addSubWidget->show();

}

void HomeWindow::on_PB_logout_clicked()
{
    std::cerr << "saving tasks\n";
    m_file->saveTasks();

    emit this->windowClosed();
}


void HomeWindow::on_PB_addTask_clicked()
{
    if (!checkInputValidity(Action::Task))
        return;

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
    if (!checkInputValidity(Action::SubTask))
        return;

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
    if (!isTask(item))
        return;

    TaskWindow* taskWindow = new TaskWindow(m_file, item, this);
    connect(taskWindow, &TaskWindow::dialogClosed, this, &HomeWindow::onDialogClosed);

    taskWindow->setModal(true);
    taskWindow->show();
}

void HomeWindow::onDialogClosed()
{
    populateTreeWidget();
}
