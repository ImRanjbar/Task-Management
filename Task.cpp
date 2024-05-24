#include "Task.h"

#include <algorithm>

Task::Task(const std::string &title, const std::string &description, const Date &deadline, bool isCompleted)
    : m_title(title), m_description(description), m_deadline(deadline), m_isCompleted(isCompleted) {}

Task::~Task() = default;

void Task::addSubTask(SubTask &newTask)
{
    m_subTasks.push_back(newTask);
}

bool Task::removeSubTask(SubTask &target)
{
    auto it = std::find(m_subTasks.begin(), m_subTasks.end(), target);

    if (it != m_subTasks.end()) {
        m_subTasks.erase(it);
        return true;
    }

    return false;
}

std::vector<SubTask> &Task::subTasks()
{
    return m_subTasks;
}

void Task::setTitle(const std::string& title)
{
    m_title = title;
}

void Task::setDescription(const std::string& description)
{
    m_description = description;
}

void Task::setDeadline(const Date& deadline)
{
    m_deadline = deadline;
}

void Task::setCompleted(bool isCompleted)
{
    m_isCompleted = isCompleted;
}

const std::string& Task::getTitle() const {
    return m_title;
}

const std::string& Task::getDescription() const {
    return m_description;
}

const Date& Task::getDeadline() const {
    return m_deadline;
}

bool Task::isCompleted() const {
    return m_isCompleted;
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
