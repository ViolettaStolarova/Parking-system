#include "Database.h"

std::vector<Admin> Database::Admins;
std::vector<Client> Database::Clients;
std::vector<Electric> Database::Electrics;
std::vector<Log> Database::Logs;
std::vector<ParkingSlot> Database::ParkingSlots;
std::vector<Ticket> Database::Tickets;
std::vector<Vehicle> Database::Vehicles;

void Database::SeedData()
{
	Admins = FileManager::getAdmins();
	Clients = FileManager::getClients();
	Electrics = FileManager::getElectrics();
	Logs = FileManager::getLogs();
	ParkingSlots = FileManager::getParkingSlots();
	Tickets = FileManager::getTickets();
	Vehicles = FileManager::getVehicles();
	FileManager::getParkingProperties();
}

void Database::SaveChanges()
{
	FileManager::setAdmins(Admins);
	FileManager::setClients(Clients);
	FileManager::setElectrics(Electrics);
	FileManager::setLogs(Logs);
	FileManager::setParkingSlots(ParkingSlots);
	FileManager::setTickets(Tickets);
	FileManager::setVehicles(Vehicles);
	FileManager::setParkingProperties();
}
