#include "ParkingSlot.h"
#include "ParkingService.h"

ParkingSlot::ParkingSlot(int Id, int TransportId)
	:Id(Id) 
{
	this->transport.setId(TransportId);
}

int ParkingSlot::getId()
{
	return this->Id;
}

int ParkingSlot::getTransportId()
{
	return this->transport.getId();
}

void ParkingSlot::setTransportId(int id)
{
	this->transport.setTransportId(id);
}

Transport ParkingSlot::getTransport()
{
	return ParkingService::getTransport(this->getTransportId());
}

Client ParkingSlot::getClient()
{
	return ParkingService::getClient(this->getTransport().getClientId());
}

bool ParkingSlot::isOccupied()
{
	return this->getTransportId() != -1;
}

void ParkingSlot::FreeUp()
{
	this->setTransportId(-1);
}