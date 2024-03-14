#include "Ticket.h"

Ticket::Ticket(int Id, int ClientId, int TransportId, std::string StartTime, bool Payed) 
	:Id(Id), Payed(Payed), StartTime(StartTime)
{ 
	this->transport.setId(TransportId);
	this->transport.setClientId(ClientId);
}

bool Ticket::isValidStartTime(const std::string& inputTime)
{
	std::regex pattern("\\d{2}:\\d{2}:\\d{2}");
	return std::regex_match(inputTime, pattern);
}

std::string Ticket::getStartTime()
{
	return this->StartTime;
}

int Ticket::getId()
{
	return this->Id;
}

int Ticket::getClientId()
{
	return this->transport.getClientId();
}

int Ticket::getTransportId()
{
	return this->transport.getId();
}

void Ticket::setTicketId(int generatedNumber)
{
	this->Id = generatedNumber;
}

void Ticket::setPayed(bool status)
{
	this->Payed = status;
}

bool Ticket::isPayed()
{
	return this->Payed;
}

int Ticket::timeToNumber(const std::string& timeString) 
{
	int hours, minutes, seconds;
	char colon;
	std::istringstream ss(timeString);
	ss >> hours >> colon >> minutes >> colon >> seconds;
	return hours * 60 + minutes + seconds / 60;
}
