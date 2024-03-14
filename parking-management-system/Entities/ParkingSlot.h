#pragma once
#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include "Transport.h"
#include "Client.h"

class ParkingSlot
{
	int Id;
	Transport transport;
public:
	ParkingSlot(int, int);

	int getId();
	int getTransportId();
	void setTransportId(int);
	Transport getTransport();
	Client getClient();
	bool isOccupied();
	void FreeUp();
};

#endif