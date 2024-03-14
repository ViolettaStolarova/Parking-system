#include "Transport.h"

Transport::Transport()
{
    this->Id = -1;
    this->PlateNumber = "";
    this->Active = false;
}

Transport::Transport(int Id, int ClientId, std::string PlateNumber, bool Active)
    : Id(Id), PlateNumber(PlateNumber), Active(Active) 
{
    this->client.setId(ClientId);
}

bool Transport::isValidPlateNumber()
{
    std::regex plateRegex("[0-9]{4}_[A-Z]{2}-[0-9]{1,2}");
    if (std::regex_match(this->PlateNumber, plateRegex)) {
        return true; 
    }
    else return false;
}

int Transport::getId()
{
    return this->Id;
}

void Transport::setId(int id)
{
    this->Id = id;
}

int Transport::getClientId()
{
    return this->client.getId();
}

void Transport::setClientId(int id)
{
    this->client.setId(id);
}

void Transport::setTransportId(int id)
{
    this->Id = id;
}

std::string Transport::getPlateNumber()
{
    return this->PlateNumber;
}

void Transport::setActive()
{
    this->Active = true;
}

void Transport::setNoActive()
{
    this->Active = false;
}

bool Transport::isActive()
{
    return this->Active;
}


