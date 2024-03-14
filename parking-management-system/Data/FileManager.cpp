#include "FileManager.h"

std::string FileManager::ADMINFILE = "Files/Admins.txt";
std::string FileManager::CLIENTFILE = "Files/Clients.txt";
std::string FileManager::LOGFILE = "Files/Logs.txt";
std::string FileManager::TICKETFILE = "Files/Tickets.txt";
std::string FileManager::VEHICLEFILE = "Files/Vehicles.txt";
std::string FileManager::ELECTRICFILE = "Files/Electrics.txt";
std::string FileManager::PARKINGSLOTSFILE = "Files/ParkingSlots.txt";
std::string FileManager::PARKINGPROPERTIESFILE = "Files/ParkingProperties.txt";

void FileManager::setAdmins(std::vector<Admin>& Admins)
{
	std::fstream file;
	file.open(ADMINFILE);

	if (file.is_open())
	{
		for (auto admin : Admins)
		{
			file << admin.getId() << ' ' << admin.getUsername() << ' ' << admin.getPassword() << "\n";
		}
	}
	file.close();
}

void FileManager::setClients(std::vector<Client>& Clients)
{
	std::fstream file;
	file.open(CLIENTFILE, std::ofstream::out | std::ofstream::trunc);

	if (file.is_open())
	{
		for (auto client : Clients)
		{
			file << client.getId() << ' ' << client.getUsername() << ' ' << client.getPassword() << ' '
				<< client.getFirstname() << ' ' << client.getLastname() << ' ' << client.getPhoneNumber() 
				<< ' ' << client.isBanned() << "\n";
		}
	}
	file.close();
}

void FileManager::setLogs(std::vector<Log>& Logs)
{
	std::fstream file;
	file.open(LOGFILE);

	if (file.is_open())
	{
		for (auto log : Logs)
		{
			file << log.getId() << ' ' << log.getClientId() << ' ' << log.getAction() << "\n";
		}
	}
	file.close();
}

void FileManager::setTickets(std::vector<Ticket>& Tickets)
{
	std::fstream file;
	file.open(TICKETFILE);

	if (file.is_open())
	{
		for (auto ticket : Tickets)
		{
			file << ticket.getId() << ' ' << ticket.getClientId() << ' ' << ticket.getTransportId() << ' '
				<< ticket.getStartTime() << ' ' << ticket.isPayed() << "\n";
		}
	}
	file.close();
}

void FileManager::setVehicles(std::vector<Vehicle>& Vehicles)
{
	std::fstream file;
	file.open(VEHICLEFILE);

	if (file.is_open())
	{
		for (auto vehicle : Vehicles)
		{
			file << vehicle.getId() << ' ' << vehicle.getClientId() << ' ' << vehicle.getPlateNumber() << ' '
				<< vehicle.isActive() << ' ' << vehicle.getType() << "\n";
		}
	}
	file.close();
}

void FileManager::setElectrics(std::vector<Electric>& Electrics)
{
	std::fstream file;
	file.open(ELECTRICFILE);

	if (file.is_open())
	{
		for (auto electric : Electrics)
		{
			file << electric.getId() << ' ' << electric.getClientId() << ' ' << electric.getPlateNumber() << ' '
				<< electric.isActive() << ' ' << electric.getBattery() << "\n";
		}
	}
	file.close();
}

void FileManager::setParkingSlots(std::vector<ParkingSlot>& ParkingSlots)
{
	std::fstream file;
	file.open(PARKINGSLOTSFILE);

	if (file.is_open())
	{
		for (auto slot : ParkingSlots)
		{
			file << slot.getId() << ' ' << slot.getTransportId() << ' ' << slot.isOccupied() << "\n";
		}
	}
	file.close();
}

void FileManager::setParkingProperties()
{
	std::fstream file;
	file.open(PARKINGPROPERTIESFILE);

	if (file.is_open())
	{
		file << ParkingProperties::VEHICLE_PRICE << ' ' << ParkingProperties::ELECTRIC_PRICE << ' ' 
			<< ParkingProperties::MAX_SLOTS << "\n";
	}
	file.close();
}


std::vector<Admin> FileManager::getAdmins()
{
	std::vector<Admin> Admins;
	std::fstream file;
	file.open(ADMINFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			std::string username;
			std::string password;

			std::istringstream iss(line);
			if (!(iss >> id >> username >> password)) break;

			Admin admin(id, username, password);
			Admins.push_back(admin);
		}
	}
	file.close();

	return Admins;
}

std::vector<Client> FileManager::getClients()
{
	std::vector<Client> Clients;
	std::fstream file;
	file.open(CLIENTFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			std::string username;
			std::string password;
			std::string firstname;
			std::string lastname;
			std::string phoneNumber;
			bool banned;

			if (line == "") break;

			std::stringstream ss(line);
			ss >> id >> username >> password >> firstname >> lastname >> phoneNumber >> banned;
			 
			Client client(id, username, password, firstname, lastname, phoneNumber, banned);
			Clients.push_back(client);
		}
	}
	file.close();

	return Clients;
}

std::vector<Log> FileManager::getLogs()
{
	std::vector<Log> Logs;
	std::fstream file;
	file.open(LOGFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			std::string action;
			int clientId;

			std::stringstream iss(line);
			if (!(iss >> id >> clientId >> action)) break;

			Log log(id, clientId, action);
			Logs.push_back(log);
		}
	}
	file.close();

	return Logs;
}

std::vector<Ticket> FileManager::getTickets()
{
	std::vector<Ticket> Tickets;
	std::fstream file;
	file.open(TICKETFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			int clientId;
			int transportId;
			std::string startTime;
			bool payed;

			std::istringstream iss(line);
			if (!(iss >> id >> clientId >> transportId >> startTime >> payed)) break;

			Ticket ticket(id, clientId, transportId, startTime, payed);
			Tickets.push_back(ticket);
		}
	}
	file.close();

	return Tickets;
}

std::vector<Vehicle> FileManager::getVehicles()
{
	std::vector<Vehicle> Vehicles;
	std::fstream file;
	file.open(VEHICLEFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			int clientId;
			std::string plateNumber;
			bool active;
			std::string type;

			std::istringstream iss(line);
			if (!(iss >> id >> clientId >> plateNumber >> active >> type)) break;

			Vehicle vehicle(id, clientId, plateNumber, active, Vehicle::stringToType(type));
			Vehicles.push_back(vehicle);
		}
	}
	file.close();

	return Vehicles;
}

std::vector<Electric> FileManager::getElectrics()
{
	std::vector<Electric> Electrics;
	std::fstream file;
	file.open(ELECTRICFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			int clientId;
			std::string plateNumber;
			bool active;
			int battery;

			std::istringstream iss(line);
			if (!(iss >> id >> clientId >> plateNumber >> active >> battery)) break;

			Electric electric(id, clientId, plateNumber, active, battery);
			Electrics.push_back(electric);
		}
	}
	file.close();

	return Electrics;
}

std::vector<ParkingSlot> FileManager::getParkingSlots()
{
	std::vector<ParkingSlot> ParkingSlots;
	std::fstream file;
	file.open(PARKINGSLOTSFILE);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int id;
			int transportId;

			std::istringstream iss(line);
			if (!(iss >> id >> transportId)) break;

			ParkingSlot parkingSlot(id, transportId);
			ParkingSlots.push_back(parkingSlot);
		}
	}
	file.close();

	return ParkingSlots;
}

void FileManager::getParkingProperties()
{
	std::fstream file;
	file.open(PARKINGPROPERTIESFILE);

	if (file.is_open())
	{
		std::string line;
		getline(file, line);
		
		std::string vehiclePrice;
		std::string electricPrice;
		std::string maxSlots;

		std::istringstream iss(line);
		iss >> vehiclePrice >> electricPrice >> maxSlots;

		if (vehiclePrice != "" && electricPrice != "" && maxSlots != "")
		{
			size_t found = vehiclePrice.find(".");
			while (found != std::string::npos) {
				vehiclePrice.replace(found, 1, ",");
				found = vehiclePrice.find(".", found + 1);
			}
			ParkingProperties::VEHICLE_PRICE = stod(vehiclePrice);

			found = electricPrice.find(".");
			while (found != std::string::npos) {
				electricPrice.replace(found, 1, ",");
				found = electricPrice.find(".", found + 1);
			}
			ParkingProperties::ELECTRIC_PRICE = stod(electricPrice);

			ParkingProperties::MAX_SLOTS = stoi(maxSlots);
		}	
	}
	file.close();
}
