#pragma once
#ifndef FILIMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>

#include "Admin.h"
#include "Client.h"
#include "Ticket.h"
#include "Vehicle.h"
#include "Electric.h"
#include "ParkingSlot.h"
#include "ParkingProperties.h"

class FileManager
{
	static std::string ADMINFILE;
	static std::string CLIENTFILE;
	static std::string LOGFILE;
	static std::string TICKETFILE;
	static std::string VEHICLEFILE;
	static std::string ELECTRICFILE;
	static std::string PARKINGSLOTSFILE;
	static std::string PARKINGPROPERTIESFILE;

public:
	static void setAdmins(std::vector<Admin>&);
	static void setClients(std::vector<Client>&);
	static void setLogs(std::vector<Log>&);
	static void setTickets(std::vector<Ticket>&);
	static void setVehicles(std::vector<Vehicle>&);
	static void setElectrics(std::vector<Electric>&);
	static void setParkingSlots(std::vector<ParkingSlot>&);
	static void setParkingProperties();

	static std::vector<Admin> getAdmins();
	static std::vector<Client> getClients();
	static std::vector<Log> getLogs();
	static std::vector<Ticket> getTickets();
	static std::vector<Vehicle> getVehicles();
	static std::vector<Electric> getElectrics();
	static std::vector<ParkingSlot> getParkingSlots();
	static void getParkingProperties();
};

#endif