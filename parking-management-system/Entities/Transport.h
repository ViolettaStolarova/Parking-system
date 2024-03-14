#pragma once
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <regex>
#include "Client.h"

class Transport
{	
protected:
	int Id;
	Client client;
	std::string PlateNumber;
	bool Active;

public:
	Transport();
	Transport(int, int, std::string, bool);

	bool isValidPlateNumber();
	int getId();
	void setId(int id);
	int getClientId();
	void setClientId(int id);
	void setTransportId(int);
	std::string getPlateNumber();
	void setActive();
	void setNoActive();
	bool isActive();
};

#endif