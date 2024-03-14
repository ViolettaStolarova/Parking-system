#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include "User.h"
#include "Log.h"
#include "ParkingSlot.h"
#include "Client.h"

class Admin : public User
{
public:
	Admin();
	Admin(int, std::string, std::string);
	Admin(const Admin&);

	std::vector<ParkingSlot> getParkingLot();
	std::vector<Log> getLogs();
	std::vector<Client> getClients();

	void changeMaxSlots(int);
	void changeElectricPrice(double);
	void changeVehiclePrice(double);
};
#endif