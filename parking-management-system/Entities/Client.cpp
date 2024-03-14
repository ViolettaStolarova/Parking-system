#include "Client.h"

#include "ParkingService.h"

Client::Client()
{
    this->Id = -1;
    this->Username = "";
    this->Password = "";
    this->Firstname = "";
    this->Lastname = "";
    this->PhoneNumber = "";
    this->Banned = 0;
}

Client::Client(int Id, std::string Username, std::string Password, std::string Firstname, std::string Lastname, std::string PhoneNumber, bool Banned)
    :User(Id, Username, Password), Firstname(Firstname), Lastname(Lastname), PhoneNumber(PhoneNumber), Banned(Banned) {}

Client::Client(const Client& client)
{
    this->Id = client.Id;
    this->Username = client.Username;
    this->Password = client.Password;
    this->Firstname = client.Firstname;
    this->Lastname = client.Lastname;
    this->PhoneNumber = client.PhoneNumber;
    this->Banned = client.Banned;
}

void Client::Pay(double payCount)
{
    std::cout << "Произвести оплату: " << payCount << " рублей" << std::endl;
}

bool Client::addTransport(std::string plateNumber, std::string type, int battery)
{
    if (type == "Electric")
        return ParkingService::addElectric(this->Id, plateNumber, battery);
    else
        return ParkingService::addVehicle(this->Id, plateNumber, type);
}

void Client::setId(int id)
{
    this->Id = id;
}

int Client::getId()
{
    return this->Id;
}

std::string Client::getFirstname()
{
    return this->Firstname;
}

void Client::setFirstname(std::string firstname)
{
    this->Firstname = firstname;
}

std::string Client::getLastname()
{
    return this->Lastname;
}

void Client::setLastname(std::string lastname)
{
    this->Lastname = lastname;
}

std::string Client::getName()
{
    return this->Lastname + ' ' + this->Firstname;
}

std::string Client::getPhoneNumber()
{
    return this->PhoneNumber;
}

bool Client::setPhoneNumber(std::string phoneNumber)
{
    this->PhoneNumber = phoneNumber;

    if (this->isValidPhoneNumber())
        return true;
    else
        return false;
}

bool Client::isBanned()
{
    return this->Banned;
}

void Client::banUnban()
{
    this->Banned = !this->Banned;
}

bool Client::isValidPhoneNumber()
{
    std::regex pattern("^\\+375\\d{9}$");
    return std::regex_match(this->PhoneNumber, pattern);

    return true;
}

