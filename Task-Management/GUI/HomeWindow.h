#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>

#include "../FileManager.h"

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class Action { Task, SubTask };

public:
    explicit HomeWindow(FileManager* file,QWidget *parent = nullptr);
    ~HomeWindow();

private:
    void populateTreeWidget();
    bool isTask(QTreeWidgetItem* item);
    void taskDone(const MyBinaryTree<Task>::Position& task);
    Date qDateToDate(QDate& qDate);

    void hideErrors(const Action& action);
    void showError(QLabel* labelError, QString error);

    void refreshWidgets(const Action& action);
    
    bool checkInputValidity(const Action& action);

signals:
    void windowClosed();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_PB_logout_clicked();

    void on_PB_addTask_clicked();

    void on_PB_addSub_clicked();

    void on_PB_done_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void onDialogClosed();

private:
    Ui::HomeWindow *ui;
    FileManager* m_file;
};

#endif // HOMEWINDOW_H
