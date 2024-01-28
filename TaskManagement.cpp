#include "TaskManagement.h"

TaskManagement::TaskManagement() : m_tasks() {}

MyBinaryTree<Task> &TaskManagement::tasks()
{
    return m_tasks;
}
