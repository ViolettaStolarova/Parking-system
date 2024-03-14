#pragma once
#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <string>
#include <iomanip>

#include "Admin.h"
#include "Client.h"

using namespace std;

class Terminal
{
public:
	static void Register();
	static void Login();

private:
	static void AdminMenu(Admin);
	static void ClientMenu(Client);
	static void AddTransport(Client);
};

#endif