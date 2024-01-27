#ifndef SUBTASK_H
#define SUBTASK_H

#include <iostream>

class SubTask
{
public:
    SubTask() = default;
    SubTask(const std::string& title, const std::string& description, const std::string& deadline, bool isCompleted = false);

    bool operator==(const SubTask& other) const;
    bool operator<(const SubTask& other) const;
    bool operator>(const SubTask& other) const;

private:
    std::string m_title;
    std::string m_description;
    std::string m_deadline;
    bool m_isCompleted;
};

#endif // SUBTASK_H
