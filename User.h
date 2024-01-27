#ifndef USER_H
#define USER_H

#include <string>
#include "TaskManagement.h"

class User
{
public:
    User();
    User(const std::string& name, const std::string& lastname, const std::string& username
         , const std::string& password, const std::string& email);

    const std::string& getName() const;
    const std::string& getLastname() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getEmail() const;

    void setName(const std::string& name);
    void setLastname(const std::string& lastname);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);

    TaskManagement& taskManagement();

private:
    std::string m_name;
    std::string m_lastname;
    std::string m_username;
    std::string m_password;
    std::string m_email;
    TaskManagement m_taskManagement;

};

#endif // USER_H
