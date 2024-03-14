#include "ParkingService.h"

#include <chrono>
#include <ctime>
#include <iomanip>

#include "Database.h"
#include "Admin.h"

std::vector<Client> ParkingService::getClients()
{
	return std::vector<Client>(Database::Clients);
}

std::vector<Log> ParkingService::getLogs()
{
	return std::vector<Log>(Database::Logs);
}

std::vector<Log> ParkingService::getLogs(std::string username)
{
	int clientId = ParkingService::getClient(username).getId();

	if (clientId == -1) return std::vector<Log>();

	std::vector<Log> ClientLogs;

	std::copy_if(Database::Logs.begin(), Database::Logs.end(), std::back_inserter(ClientLogs),
		[clientId](Log& element) { return element.getClientId() == clientId; });
	
	return ClientLogs;
}

std::vector<ParkingSlot> ParkingService::getParkingLot()
{
	return std::vector<ParkingSlot>(Database::ParkingSlots);
}

Admin ParkingService::getAdmin(std::string username, std::string password)
{
	auto it = std::find_if(Database::Admins.begin(), Database::Admins.end(),
		[=](Admin& admin) { return admin.getUsername() == username && admin.getPassword() == password; });

	if (it != Database::Admins.end())
		return Admin(*it);
	else
		return Admin();
}

Client ParkingService::getClient(std::string username, std::string password)
{
	auto it = std::find_if(Database::Clients.begin(), Database::Clients.end(),
		[=](Client& client) { return client.getUsername() == username && client.getPassword() == password; });

	if (it != Database::Clients.end())
		return Client(*it);
	else
		return Client();
}

Client ParkingService::getClient(std::string username)
{
	auto it = std::find_if(Database::Clients.begin(), Database::Clients.end(),
		[=](Client& client) { return client.getUsername() == username; });

	if (it != Database::Clients.end())
		return Client(*it);
	else
		return Client();
}

Client ParkingService::getClient(int id)
{
	auto it = std::find_if(Database::Clients.begin(), Database::Clients.end(),
		[=](Client& client) { return client.getId() == id; });

	if (it != Database::Clients.end())
		return Client(*it);
	else
		return Client();
}

Client ParkingService::addClient(std::string username, std::string password,
	std::string first_name, std::string last_name, std::string phone_number)
{
	if (username.empty() || password.empty() || first_name.empty() || last_name.empty() || phone_number.empty())
		return Client();
	if (username.length() < 4 || password.length() < 4)
		return Client();

	int id = 1;
	if (Database::Clients.size() != 0)
		id = (*(Database::Clients.end() - 1)).getId() + 1;

	Client client(id, username, password, first_name, last_name, phone_number, false);

	if (!client.isValidPhoneNumber() || ParkingService::getClient(username).getId() != -1)
		return Client();

	Database::Clients.push_back(client);

	addLog("Has_been_registred", client.getId());

	return client;
}

bool ParkingService::changeParkingProperties(std::string vehiclePrice, std::string electricPrice, std::string maxSlots)
{
	if (vehiclePrice.empty() && electricPrice.empty() && maxSlots.empty())
		return false;

	try
	{
		if (!vehiclePrice.empty())
		{
			double temp = std::stod(vehiclePrice);
			if (temp <= 0)
				return false;

			ParkingProperties::VEHICLE_PRICE = temp;
		}		
		if (!electricPrice.empty())
		{
			double temp = std::stod(electricPrice);
			if (temp <= 0)
				return false;

			ParkingProperties::ELECTRIC_PRICE = temp;
		}
		if (!maxSlots.empty())
		{
			double temp = std::stoi(maxSlots);
			if (temp <= 0)
				return false;

			ParkingProperties::MAX_SLOTS = (int) temp;
		}			
	}
	catch(const std::exception&)
	{
		return false;
	}
	

	return true;
}

Transport ParkingService::getTransport(int id)
{
	auto it1 = std::find_if(Database::Vehicles.begin(), Database::Vehicles.end(),
		[=](Vehicle& element) { return element.getId() == id; });

	if (it1 != Database::Vehicles.end())
		return Transport(*it1);

	auto it2 = std::find_if(Database::Electrics.begin(), Database::Electrics.end(),
		[=](Electric& element) { return element.getId() == id; });

	if (it2 != Database::Electrics.end())
		return Transport(*it2);
	else
	
	return Transport();
}

bool ParkingService::editClient(Client client)
{
	std::string username = client.getUsername();
	auto it = std::find_if(Database::Clients.begin(), Database::Clients.end(),
		[=](Client& element) { return element.getUsername() == username; });

	if (it == Database::Clients.end())
		return false;

	(*it).setUsername(client.getUsername());
	(*it).setPassword(client.getPassword());
	(*it).setFirstname(client.getFirstname());
	(*it).setLastname(client.getLastname());
	(*it).setPhoneNumber(client.getPhoneNumber());
	
	if (client.isBanned() != (*it).isBanned())
		(*it).banUnban();

	return true;
}

Client ParkingService::editClient(int id, std::string username, std::string password, std::string first_name, std::string last_name, std::string phone)
{
	if (username.empty() && password.empty() && first_name.empty() && last_name.empty() && phone.empty())
		return Client();

	Client client = getClient(id);

	if (!username.empty())
	{
		if (username.length() < 4 || getClient(username).getId() != -1)
			return Client();

		client.setUsername(username);
	}
	if (!password.empty())
	{
		if (password.length() < 4)
			return Client();

		client.setPassword(password);
	}
	if (!first_name.empty())
		client.setFirstname(first_name);
	if (!last_name.empty())
		client.setLastname(last_name);
	if (!phone.empty())
	{
		bool result = client.setPhoneNumber(phone);

		if (!result)
			return Client();
	}

	bool result = editClient(client);

	if (result)
	{
		addLog("Has_been_changed_profile", client.getId());

		return client;
	}
	else
		return Client();
}

bool ParkingService::addElectric(int clientId, std::string plateNumber, int battery)
{
	if (plateNumber.empty() || battery <= 0)
		return false;

	int id = 1;
	if (Database::Electrics.size() == 0 && Database::Vehicles.size() != 0)
		id = (*(Database::Vehicles.end() - 1)).getId() + 1;
	else if (Database::Vehicles.size() == 0 && Database::Electrics.size() != 0)
		id = (*(Database::Electrics.end() - 1)).getId() + 1;
	else if (Database::Vehicles.size() != 0 && Database::Electrics.size() != 0)
		id = std::max((*(Database::Vehicles.end() - 1)).getId() + 1, (*(Database::Electrics.end() - 1)).getId() + 1);	 

	Electric electric = Electric(id, clientId, plateNumber, false, battery);

	if (!electric.isValidPlateNumber())
		return false;

	Database::Electrics.push_back(electric);

	addLog("Has_been_added_transport", clientId);

	return true;
}

bool ParkingService::addVehicle(int clientId, std::string plateNumber, std::string type)
{
	if (plateNumber.empty() || type.empty())
		return false;

	int id = 1;
	if (Database::Electrics.size() == 0 && Database::Vehicles.size() != 0)
		id = (*(Database::Vehicles.end() - 1)).getId() + 1;
	else if (Database::Vehicles.size() == 0 && Database::Electrics.size() != 0)
		id = (*(Database::Electrics.end() - 1)).getId() + 1;
	else if (Database::Vehicles.size() != 0 && Database::Electrics.size() != 0)
		id = std::max((*(Database::Vehicles.end() - 1)).getId() + 1, (*(Database::Electrics.end() - 1)).getId() + 1);

	Vehicle vehicle = Vehicle(id, clientId, plateNumber, false, type);

	if (!vehicle.isValidPlateNumber())
		return false;

	Database::Vehicles.push_back(vehicle);

	addLog("Has_been_added_transport", clientId);

	return true;
}

bool ParkingService::addLog(std::string action, int clientId)
{
	int id = 1;
	if (Database::Logs.size() != 0)
		id = (*(Database::Logs.end() - 1)).getId() + 1;

	Log log = Log(id, clientId, action);
	Database::Logs.push_back(log);
	return true;
}

std::vector<std::pair<Transport, std::string>> ParkingService::getClientTransport(std::string username)
{
	std::vector<std::pair<Transport, std::string>> transport;

	Client client = ParkingService::getClient(username);
	if (client.getId() == -1)
		return transport;

	int id = client.getId();

	std::vector<Electric> electrics;
	std::copy_if(Database::Electrics.begin(), Database::Electrics.end(), std::back_inserter(electrics),
		[id](Electric& element) { return element.getClientId() == id; });
	std::vector<Vehicle> vehicles;
	std::copy_if(Database::Vehicles.begin(), Database::Vehicles.end(), std::back_inserter(vehicles),
		[id](Vehicle& element) { return element.getClientId() == id; });

	for (auto electric : electrics)
		transport.push_back(std::make_pair(Transport(electric.getId(), electric.getClientId(), 
			electric.getPlateNumber(), electric.isActive()), "Electric"));
	for (auto vehicle : vehicles)
		transport.push_back(std::make_pair(Transport(vehicle.getId(), vehicle.getClientId(),
			vehicle.getPlateNumber(), vehicle.isActive()), vehicle.getType()));

	return transport;
}

bool ParkingService::deleteTransport(std::string plateNumber)
{
	std::pair<Transport, std::string> transport = getTransport(plateNumber);

	int id = transport.first.getId();

	if (transport.second == "")
		return false;

	try
	{
		if (transport.second == "Electric")
		{
			auto new_end = std::remove_if(Database::Electrics.begin(), Database::Electrics.end(),
				[=](Electric& electric) { return electric.getId() == id; });
			Database::Electrics.erase(new_end, Database::Electrics.end());
		}	
		else
		{
			auto new_end = std::remove_if(Database::Vehicles.begin(), Database::Vehicles.end(),
				[=](Vehicle& vehicle) { return vehicle.getId() == id; });
			Database::Vehicles.erase(new_end, Database::Vehicles.end());
		}
			
		addLog("Has_been_deleted_transport", transport.first.getClientId());

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

std::pair<Transport, std::string> ParkingService::getTransport(std::string plateNumber)
{
	auto electric = std::find_if(Database::Electrics.begin(), Database::Electrics.end(),
		[=](Electric& element) { return element.getPlateNumber() == plateNumber; });
	auto vehicle = std::find_if(Database::Vehicles.begin(), Database::Vehicles.end(),
		[=](Vehicle& element) { return element.getPlateNumber() == plateNumber; });

	if (electric != Database::Electrics.end())
		return std::make_pair(Transport((*electric).getId(), (*electric).getClientId(),
			(*electric).getPlateNumber(), (*electric).isActive()), "Electric");
	if (vehicle != Database::Vehicles.end())
		return std::make_pair(Transport((*vehicle).getId(), (*vehicle).getClientId(),
			(*vehicle).getPlateNumber(), (*vehicle).isActive()), (*vehicle).getType());

	return std::make_pair(Transport(), "");
}

std::vector<Ticket> ParkingService::getClientTickets(int clientId)
{
	std::vector<Ticket> tickets;
	std::copy_if(Database::Tickets.begin(), Database::Tickets.end(), std::back_inserter(tickets),
		[clientId](Ticket& ticket) { return ticket.getClientId() == clientId; });

	return tickets;
}

double ParkingService::getPrice(int clientId)
{
	auto it1 = std::find_if(Database::Vehicles.begin(), Database::Vehicles.end(),
		[=](Vehicle& element) { return element.getClientId() == clientId && element.isActive(); });
	auto it2 = std::find_if(Database::Electrics.begin(), Database::Electrics.end(),
		[=](Electric& element) { return element.getClientId() == clientId && element.isActive(); });

	if (it1 != Database::Vehicles.end())
	{
		auto ticket = std::find_if(Database::Tickets.begin(), Database::Tickets.end(),
			[=](Ticket& ticket) { return ticket.getTransportId() == (*it1).getId(); });

		std::tm tm = {};
		std::istringstream ss((*ticket).getStartTime());
		ss >> std::get_time(&tm, "%Y-%m-%d_%H:%M:%S");
		std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::seconds diff = std::chrono::duration_cast<std::chrono::seconds>(now - timePoint);

		return round((((double)diff.count()) / 3600) * ParkingProperties::ELECTRIC_PRICE * 100) / 100;

	}
	if (it2 != Database::Electrics.end())
	{
		auto ticket = std::find_if(Database::Tickets.begin(), Database::Tickets.end(),
			[=](Ticket& ticket) { return ticket.getTransportId() == (*it2).getId(); });

		std::tm tm = {};
		std::istringstream ss((*ticket).getStartTime());
		ss >> std::get_time(&tm, "%Y-%m-%d_%H:%M:%S");
		std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::seconds diff = std::chrono::duration_cast<std::chrono::seconds>(now - timePoint);

		return round((((double)diff.count()) / 3600) * ParkingProperties::ELECTRIC_PRICE * 100) / 100;
	}

	return -1;
}

void ParkingService::Pay(int clientId)
{
	auto vehicle = std::find_if(Database::Vehicles.begin(), Database::Vehicles.end(),
		[=](Vehicle& element) { return element.getClientId() == clientId && element.isActive(); });
	auto electric = std::find_if(Database::Electrics.begin(), Database::Electrics.end(),
		[=](Electric& element) { return element.getClientId() == clientId && element.isActive(); });

	int active = 0;
	if (vehicle != Database::Vehicles.end())
	{
		(*vehicle).setNoActive();
		active = (*vehicle).getId();
	}	
	else
	{
		(*electric).setNoActive();
		active = (*electric).getId();
	}
		

	auto ticket = std::find_if(Database::Tickets.begin(), Database::Tickets.end(),
		[=](Ticket& element) { return element.getClientId() == clientId && !element.isPayed(); });
	(*ticket).setPayed(true);

	auto slot = std::find_if(Database::ParkingSlots.begin(), Database::ParkingSlots.end(),
		[=](ParkingSlot& element) { return element.getTransportId() == active; });
	(*slot).FreeUp();

	addLog("Has_been_payed", clientId);
	addLog("Has_been_left", clientId);
}

bool ParkingService::Occupate(int clientId, std::string plateNumber)
{
	Transport transport = getTransport(plateNumber).first;
	if (transport.getId() == -1)
		return false;

	auto vehicle = std::find_if(Database::Vehicles.begin(), Database::Vehicles.end(),
		[=](Vehicle& element) { return element.getClientId() == clientId && element.isActive(); });
	auto electric = std::find_if(Database::Electrics.begin(), Database::Electrics.end(),
		[=](Electric& element) { return element.getClientId() == clientId && element.isActive(); });
	if (vehicle != Database::Vehicles.end() || electric != Database::Electrics.end())
		return false;

	auto slot = std::find_if(Database::ParkingSlots.begin(), Database::ParkingSlots.end(),
		[=](ParkingSlot& element) { return !element.isOccupied(); });
	if (slot != Database::ParkingSlots.end())
		(*slot).setTransportId(transport.getId());
	else
	{
		if (Database::ParkingSlots.size() == ParkingProperties::MAX_SLOTS)
			return false;

		int id = 1;
		if (Database::ParkingSlots.size() != 0)
			id = (*(Database::ParkingSlots.end() - 1)).getId() + 1;

		Database::ParkingSlots.push_back(ParkingSlot(id, transport.getId()));
	}


	vehicle = std::find_if(Database::Vehicles.begin(), Database::Vehicles.end(),
		[=](Vehicle& element) { return element.getPlateNumber() == plateNumber; });
	electric = std::find_if(Database::Electrics.begin(), Database::Electrics.end(),
		[=](Electric& element) { return element.getPlateNumber() == plateNumber; });
	if (vehicle != Database::Vehicles.end())
		(*vehicle).setActive();
	else
		(*electric).setActive();

	int id = 1;
	if (Database::Tickets.size() != 0)
		id = (*(Database::Tickets.end() - 1)).getId() + 1;

	std::time_t now = std::time(nullptr);
	std::tm tm;
	localtime_s(&tm, &now);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d_%H:%M:%S");
	std::string formattedDateTime = oss.str();

	Database::Tickets.push_back(Ticket(id, clientId, transport.getId(), formattedDateTime, false));

	addLog("Has_been_occupated", clientId);

	return true;
}

bool ParkingService::editRole(std::string username)
{
	Client client = getClient(username);

	if (client.getId() == -1)
		return false;

	int id = 1;
	if (Database::Admins.size() != 0)
		id = (*(Database::Admins.end() - 1)).getId() + 1;

	Admin admin = Admin(id, username, client.getPassword());
	Database::Admins.push_back(admin);

	auto new_end = std::remove_if(Database::Clients.begin(), Database::Clients.end(),
		[=](Client& client) { return client.getUsername() == username; });
	Database::Clients.erase(new_end, Database::Clients.end());

	return true;
}