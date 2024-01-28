#include "FileManager.h"
#include <fstream>

FileManager::FileManager(User& user) : m_user(&user) {}

FileManager::status FileManager::searchUser()
{
    std::ifstream file("users.txt");

    if (!file)
        throw std::runtime_error("Can't open file\n");

    std::string temp;
    while (file >> temp) {
        if (temp == m_user->getUsername()) {
            file >> temp;
            if (temp == m_user->getPassword()) {
                file.close();
                return status::success;
            }
            else {
                file.close();
                return status::wrongPass;
            }
        }
    }

    file.close();
    return status::wrongUsername;
}

bool FileManager::readData()
{
    if (searchUser() == status::success) {
        std::string filePath = "./Tasks/" + m_user->getUsername() + ".txt";
        std::ifstream file(filePath);

        if (!file){
            std::cerr << "Can't open file\n";
            return false;
        }

        std::string temp;
        while (std::getline(file, temp)) {
            std::string title = temp;

            std::string description;
            std::getline(file, description);

            int year, month, day;
            file >> year >> month >> day;
            Date deadline(day, month, year);


            int numSub;
            file >> numSub;

            Task newTask(title, description, deadline, false);
            m_user->taskManagement().tasks().insert(newTask);
            file.ignore();

            while (numSub > 0) {
                std::string title;
                std::getline(file, title);

                std::string description;
                std::getline(file, description);

                int year, month, day;
                file >> year >> month >> day;
                Date deadline(day, month, year);


                SubTask sub(title, description, deadline, false);

                newTask.addSubTask(sub);

                numSub--;
                file.ignore();
            }
        }

        file.close();

        return true;
    }
    else
        return false;

}

bool FileManager::addUser()
{
    std::ofstream file("Users.txt", std::ofstream::app);

    if (!file) {
        std::cerr << "Can't open file\n";
        return false;
    }

    file << m_user->getUsername() << " "
         << m_user->getPassword() << " "
         << m_user->getName() << " "
         << m_user->getLastname() << " "
         << m_user->getEmail() << '\n';

    file.close();

    return true;
}

bool FileManager::saveTasks()
{
    std::string filePath = "./Tasks/" + m_user->getUsername() + ".txt";
    std::ofstream file(filePath);

    if (!file) {
        std::cerr << "Can't open file\n";
        return false;
    }

    std::list<Task> tasks = m_user->taskManagement().tasks().levelOrderList();
    for (Task& task : tasks) {
        file << task.getTitle() << '\n';
        file << task.getDescription() << '\n';
        file << task.getDeadline().getYear() << " " << task.getDeadline().getMonth() << " " << task.getDeadline().getDay() << '\n';
        file << task.subTasks().size() << '\n';

        std::vector<SubTask> subs = task.subTasks();

        for (SubTask& sub : subs) {
            file << sub.getTitle() << '\n';
            file << sub.getDescription() << '\n';
            file << sub.getDeadline().getYear() << " " << sub.getDeadline().getMonth() << " " << sub.getDeadline().getDay() << '\n';
        }

    }

    file.close();


    return true;
}
