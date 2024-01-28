#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "../FileManager.h"

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(FileManager* file,QWidget *parent = nullptr);
    ~HomeWindow();

signals:
    void windowClosed();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_PB_logout_clicked();

private:
    Ui::HomeWindow *ui;
    FileManager* m_file;
};

#endif // HOMEWINDOW_H
