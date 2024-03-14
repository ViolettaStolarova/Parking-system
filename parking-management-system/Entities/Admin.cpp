#include "Admin.h"

#include "ParkingProperties.h"
#include "ParkingService.h"

Admin::Admin():User() {}

Admin::Admin(int Id,  std::string Username, std::string Password)
	:User(Id, Username, Password) {}

Admin::Admin(const Admin& admin)
{
	this->Id = admin.Id;
	this->Username = admin.Username;
	this->Password = admin.Password;
}

std::vector<ParkingSlot> Admin::getParkingLot()
{
	return ParkingService::getParkingLot();
}

std::vector<Log> Admin::getLogs()
{
	return ParkingService::getLogs();
}

std::vector<Client> Admin::getClients()
{
	return ParkingService::getClients();
}

void Admin::changeMaxSlots(int newCountOfSlots)
{
	ParkingProperties::MAX_SLOTS = newCountOfSlots;
}

void Admin::changeElectricPrice(double newPrice)
{
	ParkingProperties::ELECTRIC_PRICE = newPrice;
}

void Admin::changeVehiclePrice(double newPrice)
{
	ParkingProperties::VEHICLE_PRICE = newPrice;
}
