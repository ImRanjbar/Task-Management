#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

class Task
{
public:
    Task() = default;
    Task(const std::string& title, const std::string& description, const std::string& deadline, bool isCompleted = false);

    void addSubTask(Task& newTask);
    bool removeSubTask(Task& target);
    std::vector<Task>& subTasks();

    bool operator==(const Task& other) const;
    bool operator<(const Task& other) const;
    bool operator>(const Task& other) const;

private:
    std::string m_title;
    std::string m_description;
    std::string m_deadline;
    bool m_isCompleted;
    std::vector<Task> m_subTasks;
};

#endif // TASK_H
