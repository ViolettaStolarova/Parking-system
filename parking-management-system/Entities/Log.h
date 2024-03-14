#pragma once
#ifndef LOG_H
#define LOG_H

#include <string>

#include "Client.h"

class Log
{
	int Id;
	std::string Action;
	Client client;
public:
	Log(int, int, std::string);

	int getId();
	int getClientId();
	Client getClient();
	std::string getAction();
	std::string setAction(const std::string&);
};

#endif