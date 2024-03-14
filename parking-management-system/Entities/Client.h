#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <regex>

#include "User.h"

class Client : public User
{
	std::string Firstname;
	std::string Lastname;
	std::string PhoneNumber;
	bool Banned;

public:
	Client();
	Client(int, std::string, std::string, std::string, std::string, std::string, bool);
	Client(const Client&);

	void Pay(double);
	bool addTransport(std::string, std::string, int = 0);
	
	void setId(int id);
	int getId();
	std::string getFirstname();
	void setFirstname(std::string);
	std::string getLastname();
	void setLastname(std::string);
	std::string getPhoneNumber();
	bool setPhoneNumber(std::string);
	std::string getName();
	void banUnban();
	bool isBanned();
	bool isValidPhoneNumber();
};

#endif