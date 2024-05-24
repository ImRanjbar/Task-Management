#include "FileManager.h"
#include <limits>
#include <fstream>

FileManager::FileManager(User& user) : m_user(&user) {}

FileManager::~FileManager()
{
    if (m_user){
        delete m_user;
        m_user = nullptr;
    }
}

FileManager::status FileManager::searchUser() const
{
    return searchUser(m_user->getUsername(), m_user->getPassword());
}

FileManager::status FileManager::searchUser(const std::string &username, const std::string& password)
{
    std::ifstream file("Users.txt");

    if (!file)
        throw std::runtime_error("Can't open file\n");

    std::string temp;
    while (file >> temp) {
        if (temp == username) {
            file >> temp;
            if (temp == password) {
                file.close();
                return status::success;
            }
            else {
                file.close();
                return status::wrongPass;
            }
        }
        else {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    file.close();
    return status::wrongUsername;

}

User &FileManager::user()
{
    return *m_user;
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
            file.ignore();

            Task newTask(title, description, deadline, false);

            if (numSub){
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

                m_user->taskManagement().tasks().insert(newTask);
            }
            else {
                m_user->taskManagement().tasks().insert(newTask);
            }
        }

        file.close();

        return true;
    }

    else
        return false;
}

bool FileManager::readUser()
{
    std::ifstream file("Users.txt");

    if (!file){
        std::cerr << "Can't open Users file\n";
        return false;
    }

    std::string str;
    while (file >> str){
        if (str != m_user->getUsername()){
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::numeric_limits<int>::max();
        }
        else {
            m_user->setUsername(str);
            file >> str;
            m_user->setPassword(str);
            file >> str;
            m_user->setName(str);
            file >> str;
            m_user->setLastname(str);
            file >> str;
            m_user->setEmail(str);

            file.close();
            return true;
        }
    }

    file.close();
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
