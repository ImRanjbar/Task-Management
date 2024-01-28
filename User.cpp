#include "User.h"

User::User() : m_name(""), m_lastname(""), m_username(""), m_password(""), m_email(""), m_taskManagement() {}

User::User(const std::string &name, const std::string &lastname, const std::string &username, const std::string &password, const std::string &email) :
    m_name(name), m_lastname(lastname), m_username(username), m_password(password), m_email(email), m_taskManagement() {}

const std::string& User::getName() const {
    return m_name;
}

const std::string& User::getLastname() const {
    return m_lastname;
}

const std::string& User::getUsername() const {
    return m_username;
}

const std::string& User::getPassword() const {
    return m_password;
}

const std::string& User::getEmail() const {
    return m_email;
}

void User::setName(const std::string& name) {
    m_name = name;
}

void User::setLastname(const std::string& lastname) {
    m_lastname = lastname;
}

void User::setUsername(const std::string& username) {
    m_username = username;
}

void User::setPassword(const std::string& password) {
    m_password = password;
}

void User::setEmail(const std::string& email) {
    m_email = email;
}

TaskManagement& User::taskManagement()
{
    return m_taskManagement;
}
