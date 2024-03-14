#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include "Transport.h"

#include <string>

class Vehicle : public Transport
{
	enum class Type {Car, Motorbike, Lorry};
	Type type;
public:
	Vehicle(int, int, std::string, bool, Type);
	Vehicle(int, int, std::string, bool, std::string);\
	std::string getType(); 
	static Type stringToType(std::string&);
	void setType(Type);
};

#endif