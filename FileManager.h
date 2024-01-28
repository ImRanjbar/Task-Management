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

    status searchUser();

    bool readData();
    bool addUser();
    bool saveTasks();

private:
    User* m_user;
};

#endif // FILEMANAGER_H
