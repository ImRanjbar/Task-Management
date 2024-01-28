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
    populateTreeWidget();

    ui->addSubWidget->hide();

    ui->DE_deadlineSub->setDate(QDate::currentDate());
    ui->DE_deadlineTask->setDate(QDate::currentDate());
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
}

void HomeWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->addSubWidget->show();
    ui->LB_taskTitle->setText("Title: "+ item->text(0));

}

void HomeWindow::on_PB_logout_clicked()
{
    emit this->windowClosed();
}


void HomeWindow::on_PB_addTask_clicked()
{
    std::string title = ui->LE_titleTask->text().trimmed().toStdString();
    std::string description = ui->TE_desTask->toPlainText().trimmed().toStdString();
    int day = ui->DE_deadlineTask->date().day();
    int month = ui->DE_deadlineTask->date().month();
    int year = ui->DE_deadlineTask->date().year();
    Date deadline(day, month, year);

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
    QDate date = QDate::fromString(selectedItem->text(2).trimmed(), "d/M/yyyy");
    int taskDay = date.day();
    int taskMonth = date.month();
    int taskYear = date.year();

    Date taskDeadline(taskDay, taskMonth, taskYear);
    Task desiredTask(taskTitle, taskDescription, taskDeadline);
    std::cerr << desiredTask.getTitle() << " " << desiredTask.getDescription() << " " << desiredTask.getDeadline().toString() << "\n";
    MyBinaryTree<Task>::Position positionTask = m_file->user().taskManagement().tasks().editElement(desiredTask);

    Task& realTask = *positionTask;


    // add SubTask to realTask
    std::string title = ui->LE_titleSub->text().trimmed().toStdString();
    std::string description = ui->TE_desSub->toPlainText().trimmed().toStdString();
    int day = ui->DE_deadlineSub->date().day();
    int month = ui->DE_deadlineSub->date().month();
    int year = ui->DE_deadlineSub->date().year();
    Date deadline(day, month, year);
    SubTask newSub(title, description, deadline);

    realTask.addSubTask(newSub);

    populateTreeWidget();
}

