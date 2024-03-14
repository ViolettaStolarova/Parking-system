#pragma once
#ifndef PARKINGSERVICE_H
#define PARKINGSERVICE_H

#include <vector>
#include <algorithm>

#include "Admin.h"
#include "Client.h"
#include "Electric.h"
#include "Log.h"
#include "ParkingSlot.h"
#include "Ticket.h"
#include "Vehicle.h"

class ParkingService
{
public:
	static std::vector<Client> getClients();
	static std::vector<Log> getLogs();
	static std::vector<Log> getLogs(std::string);
	static std::vector<ParkingSlot> getParkingLot();
	static bool changeParkingProperties(std::string, std::string, std::string);
	static Admin getAdmin(std::string, std::string);
	static Client getClient(std::string, std::string);
	static Client getClient(std::string);
	static Client getClient(int);
	static Client addClient(std::string, std::string, std::string, std::string, std::string);
	static Transport getTransport(int);
	static bool editClient(Client);
	static Client editClient(int id, std::string, std::string, std::string, std::string, std::string);
	static bool addElectric(int, std::string, int);
	static bool addVehicle(int, std::string, std::string);
	static bool addLog(std::string, int);
	static std::vector<std::pair<Transport, std::string>> getClientTransport(std::string);
	static bool deleteTransport(std::string);
	static std::pair<Transport, std::string> getTransport(std::string);
	static std::vector<Ticket> getClientTickets(int);
	static double getPrice(int);
	static void Pay(int);
	static bool Occupate(int, std::string);
	static bool editRole(std::string);
};

#endif