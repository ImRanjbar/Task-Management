#include "TaskManagement.h"

TaskManagement::TaskManagement() : m_tasks() {}

TaskManagement::~TaskManagement() = default;

MyBinaryTree<Task> &TaskManagement::tasks()
{
    return m_tasks;
}
