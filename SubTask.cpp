#include "SubTask.h"

SubTask::SubTask(const std::string &title, const std::string &description, const std::string &deadline, bool isCompleted)
    : m_title(title), m_description(description), m_deadline(deadline), m_isCompleted(isCompleted) {}


bool SubTask::operator==(const SubTask &other) const
{
    return m_title == other.m_title &&
           m_description == other.m_description &&
           m_deadline == other.m_deadline &&
           m_isCompleted == other.m_isCompleted;
}

bool SubTask::operator<(const SubTask &other) const
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

bool SubTask::operator>(const SubTask &other) const
{
    if (!(*this < other))
        return true;
    else
        return false;
}
