#pragma once
#ifndef ELECTRIC_H
#define ELECTRIC_H

#include "Transport.h"

class Electric : public Transport
{
	int Battery;
public:
	Electric(int, int, std::string, bool, int);

	int getBattery();
	void setBattery(int);
};

#endif