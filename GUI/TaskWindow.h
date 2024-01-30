#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "../FileManager.h"

namespace Ui {
class TaskWindow;
}

class TaskWindow : public QDialog
{
    Q_OBJECT

public:
    enum class Action { Task, SubTask };

public:
    explicit TaskWindow(FileManager* file, QTreeWidgetItem* item, QWidget *parent = nullptr);
    ~TaskWindow();

private:
    Date qDateToDate(QDate& qDate);
    MyBinaryTree<Task>::Position findTask();
    bool isTask();
    void edit(const Action& action);

signals:
    void dialogClosed();

private slots:
    void on_PB_edit_clicked();

private:
    Ui::TaskWindow *ui;
    QTreeWidgetItem* m_item;
    FileManager* m_file;
};

#endif // TASKWINDOW_H
