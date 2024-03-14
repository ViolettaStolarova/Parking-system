#include "User.h"

User::User()
{
    this->Id = -1;
    this->Username = "";
    this->Password = "";
}

User::User(int Id, std::string Username, std::string Password)
    :Id(Id), Username(Username), Password(Password) {}

int User::getId()
{
    return this->Id;
}

std::string User::getUsername()
{
    return this->Username;
}

void User::setUsername(std::string username)
{
    this->Username = username;
}

std::string User::getPassword()
{
    return this->Password;
}

void User::setPassword(std::string password)
{
    this->Password = password;
}


