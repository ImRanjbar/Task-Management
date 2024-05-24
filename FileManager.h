#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "User.h"

class FileManager
{
public:
    enum status {
        success,
        wrongPass,
        wrongUsername
    };

public:
    FileManager(User& user);
    ~FileManager();

    status searchUser() const;
    static status searchUser(const std::string& username, const std::string& password = "");

    User& user();

    bool readData();
    bool readUser();
    bool addUser();
    bool saveTasks();

private:
    User* m_user;
};

#endif // FILEMANAGER_H
