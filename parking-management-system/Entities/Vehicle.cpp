#include "Vehicle.h"

Vehicle::Vehicle(int Id, int ClientId, std::string PlateNumber, bool Active, Type type)
	: Transport(Id, ClientId, PlateNumber, Active), type(type) {}

Vehicle::Vehicle(int Id, int ClientId, std::string PlateNumber, bool Active, std::string type)
{
	this->Id = Id;
	this->client.setId(ClientId);
	this->PlateNumber = PlateNumber;
	this->Active = Active;
	this->type = this->stringToType(type);
}

std::string Vehicle::getType()
{
	if (this->type == Type::Car) {
		return "Car";
	}
	else if (this->type == Type::Motorbike) {
		return "Motorbike";
	}
	else if (this->type == Type::Lorry) {
		return "Lorry";
	}
	else {
		return "Unknown";
	}
}

void Vehicle::setType(Type newType)
{
	this->type = newType;
}

Vehicle::Type Vehicle::stringToType(std::string& str)
{
	if (str == "Car") {
		return Type::Car;
	}
	else if (str == "Motorbike") {
		return Type::Motorbike;
	}
	else if (str == "Lorry") {
		return Type::Lorry;
	}
	return Type::Car;
}

