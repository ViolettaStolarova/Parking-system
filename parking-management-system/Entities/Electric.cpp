#include "Electric.h"

Electric::Electric(int Id, int ClientId, std::string PlateNumber, bool Active, int Battery)
	: Transport(Id, ClientId, PlateNumber, Active), Battery(Battery) {}

int Electric::getBattery()
{
	return this->Battery;
}

void Electric::setBattery(int battery)
{
	this->Battery = battery;
}
