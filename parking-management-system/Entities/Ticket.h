#pragma once
#ifndef	TICKET_H
#define TICKET_H

#include <string>
#include <regex>
#include <sstream>
#include "Transport.h"

class Ticket
{
	int Id;
	std::string StartTime;
	bool Payed;
	Transport transport;

public:
	Ticket(int, int, int, std::string, bool);

	bool isValidStartTime(const std::string&);
	std::string getStartTime();
	int getId();
	int getClientId();
	int getTransportId();
	void setTicketId(int);
	void setPayed(bool);
	bool isPayed();
	int timeToNumber(const std::string&);
};

#endif