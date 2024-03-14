#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Admin.h"
#include "Client.h"
#include "Electric.h"
#include "Log.h"
#include "ParkingSlot.h"
#include "Ticket.h"
#include "Vehicle.h"
#include "FileManager.h"

class Database
{
public:
	static std::vector<Admin> Admins;
	static std::vector<Client> Clients;
	static std::vector<Electric> Electrics;
	static std::vector<Log> Logs;
	static std::vector<ParkingSlot> ParkingSlots;
	static std::vector<Ticket> Tickets;
	static std::vector<Vehicle> Vehicles;

	static void SeedData();
	static void SaveChanges();
};

#endif

