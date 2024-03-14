#include "Log.h"
#include "ParkingService.h"

Log::Log(int Id, int ClientId, std::string Action)
	:Id(Id), Action(Action) {
	this->client.setId(ClientId);
}

int Log::getId()
{
	return this->Id;
}

int Log::getClientId()
{
	return this->client.getId();
}

Client Log::getClient()
{
	return ParkingService::getClient(this->client.getId());
}

std::string Log::getAction()
{
	return this->Action;
}

std::string Log::setAction(const std::string& action)
{
	return this->Action = action;
}

