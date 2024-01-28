#ifndef TASKMANAGEMENT_H
#define TASKMANAGEMENT_H

#include "MyBinaryTree.h"
#include "Task.h"

class TaskManagement
{
public:
    TaskManagement();
    MyBinaryTree<Task>& tasks();

private:
    MyBinaryTree<Task> m_tasks;
};

#endif // TASKMANAGEMENT_H
