#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include "SubTask.h"

class Task
{
public:
    Task() = default;
    Task(const std::string& title, const std::string& description, const Date& deadline, bool isCompleted = false);
    ~Task();

    void addSubTask(SubTask& newTask);
    bool removeSubTask(SubTask& target);
    std::vector<SubTask>& subTasks();

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setDeadline(const Date& deadline);
    void setCompleted(bool isCompleted);

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const Date& getDeadline() const;
    bool isCompleted() const;

    bool operator==(const Task& other) const;
    bool operator<(const Task& other) const;
    bool operator>(const Task& other) const;

private:
    std::string m_title;
    std::string m_description;
    Date m_deadline;
    bool m_isCompleted;
    std::vector<SubTask> m_subTasks;
};

#endif // TASK_H
