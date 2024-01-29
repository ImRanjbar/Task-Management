#ifndef SUBTASK_H
#define SUBTASK_H

#include <iostream>
#include "Date.h"

class SubTask
{
public:
    SubTask() = default;
    SubTask(const std::string& title, const std::string& description, const Date& deadline, bool isCompleted = false);
    ~SubTask();

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const Date& getDeadline() const;
    bool isCompleted() const;

    bool operator==(const SubTask& other) const;
    bool operator<(const SubTask& other) const;
    bool operator>(const SubTask& other) const;

private:
    std::string m_title;
    std::string m_description;
    Date m_deadline;
    bool m_isCompleted;
};

#endif // SUBTASK_H
