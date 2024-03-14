#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User
{
protected:
	int Id;
	std::string Password;
	std::string Username;

public:
	User();
	User(int, std::string, std::string);

	int getId();
	std::string getUsername();
	void setUsername(std::string);
	std::string getPassword();
	void setPassword(std::string);
};
#endif