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
    explicit TaskWindow(FileManager* file, QTreeWidgetItem* item, QWidget *parent = nullptr);
    ~TaskWindow();


signals:
    void dialogClosed();

private:
    Ui::TaskWindow *ui;
    QTreeWidgetItem* m_item;
    FileManager* m_file;
};

#endif // TASKWINDOW_H
