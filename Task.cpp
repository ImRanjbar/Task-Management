#include "Task.h"

#include <algorithm>

Task::Task(const std::string &title, const std::string &description, const std::string &deadline, bool isCompleted)
    : m_title(title), m_description(description), m_deadline(deadline), m_isCompleted(isCompleted) {}

void Task::addSubTask(Task &newTask)
{
    m_subTasks.push_back(newTask);
}

bool Task::removeSubTask(Task &target)
{
    auto it = std::find(m_subTasks.begin(), m_subTasks.end(), target);

    if (it != m_subTasks.end()) {
        m_subTasks.erase(it);
        return true;
    }

    return false;
}

bool Task::operator==(const Task &other) const
{
    return m_title == other.m_title &&
           m_description == other.m_description &&
           m_deadline == other.m_deadline &&
           m_isCompleted == other.m_isCompleted;
}

bool Task::operator<(const Task &other) const
{
    if (m_deadline < other.m_deadline){
        return true;
    }
    else if (m_deadline > other.m_deadline) {
        return false;
    }
    else {
        if (m_title < other.m_title)
            return true;
        else
            return false;
    }
}

bool Task::operator>(const Task &other) const
{
    if (!(*this < other))
        return true;
    else
        return false;
}
