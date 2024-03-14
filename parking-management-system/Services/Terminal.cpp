#include "Terminal.h"

#include "ParkingService.h"
#include "CheckInput.h"

void Terminal::Login()
{
	system("cls");

	while (true)
	{
		string username, password;

		cin.ignore(32767, '\n');

		cout << "������� �����: ";
		getline(cin, username);

		cout << "������� ������: ";
		getline(cin, password);

		Admin admin = ParkingService::getAdmin(username, password);
		if (admin.getId() != -1)
		{
			AdminMenu(admin);
			return;
		}

		Client client = ParkingService::getClient(username, password);
		if (client.getId() != -1)
		{
			ClientMenu(client);
			return;
		}
		
		cout << endl << "�������� ������. ������ �����? (1)" << endl;		
		if (CheckInput::check_exit_choice()) break;
		cout << endl;
	}
}

void Terminal::Register()
{
	system("cls");

	while (true)
	{
		string username, password, first_name, last_name, phone_number;

		cin.ignore(32767, '\n');
		cout << "������� �����: ";
		getline(cin, username);
		cout << "������� ������: ";
		getline(cin, password);
		cout << "������� ���� ���: ";
		getline(cin, first_name);
		cout << "������� ���� �������: ";
		getline(cin, last_name);
		cout << "������� ��� ����� ��������: ";
		getline(cin, phone_number);

		Client client = ParkingService::addClient(username, password, first_name, last_name, phone_number);
		if (client.getId() != -1)
		{
			cout << "�� ������� ������������������!" << endl;
			char e; cin >> e;
			break;
		}

		cout << endl << "�������� ������. ������ �����? (1)" << endl;
		if (CheckInput::check_exit_choice()) break;
		cout << endl;
	}
}

void Terminal::AdminMenu(Admin admin)
{
	while (true)
	{
		system("cls");
		cout << "������, " << admin.getUsername() << "!" << endl << endl;

		cout <<	"�������� �������� ��������:" << endl <<
				"1 �������� ������ ��������" << endl <<
				"2 �������� ������ ����������� ����" << endl <<
				"3 �������� �������� �������������" << endl <<
				"4 �������� �������� ������������ ������������" << endl <<
				"5 �������������/�������������� ������������" << endl <<
				"6 �������� �������������� ��������" << endl <<
				"7 �������� ���� ������������" << endl <<
				"8 �����" << endl << endl;

		int choice = CheckInput::check_choice(1, 8);

		Client client;
		int width = 20;
		vector<Client> clients;
		vector<ParkingSlot> slots;
		vector<Log> logs;
		string username = "";
		char e; 

		switch (choice)
		{
		case 1:
			system("cls");
			cout << "������ ��������..." << endl << endl;

			cout << "Id" << setw(width) << "�����" 
			     << setw(width) << "���" << setw(width) << "�������" 
			     << setw(width) << "������" << endl << endl;
			
			clients = ParkingService::getClients();
			for (auto client : clients)
				cout << client.getId() << setw(width) << client.getUsername()
				     << setw(width) << client.getName() << setw(width) << client.getPhoneNumber()
					 << setw(width) << ((client.isBanned()) ? "�������" : "�� �������") << endl;
			cout << endl;

			cin >> e;
			break;

		case 2:
			system("cls");
			cout << "������ ����������� ����..." << endl << endl;

			cout << "Id" << setw(width) << "������"
				 << setw(width) << "������" << setw(width) << "����� ����������" 
				 << endl << endl;

			slots = ParkingService::getParkingLot();
			for (auto slot : slots)
				cout << slot.getId() << setw(width) << ((slot.isOccupied()) ? "������" : "�� ������")
					 << setw(width) << slot.getClient().getName() << setw(width)
				     << setw(width) << slot.getTransport().getPlateNumber() << endl;
			cout << endl;

			cin >> e;
			break;

		case 3:
			system("cls");
			cout << "�������� �������������..." << endl << endl;

			cout << "Id" << setw(width) << "��������" << setw(width) 
				 << "�����" << endl << endl;

			logs = ParkingService::getLogs();
			for (auto log : logs)
				cout << log.getId() << setw(width) << log.getAction() << setw(width)
					 << log.getClient().getUsername() << endl;
			cout << endl;					 

			cin >> e;
			break;
			
		case 4:
			system("cls");
			cout << "�������� ������������ ������������..." << endl << endl;

			while (true)
			{
				cin.ignore(32767, '\n');
				cout << "������� ��� ������������: ";
				getline(cin, username);

				if (ParkingService::getClient(username).getId() == -1)
				{
					cout << endl << "�������� ������. ������ �����? (1)" << endl;
					if (CheckInput::check_exit_choice()) break;
					cout << endl;

					continue;
				}

				cout << "Id" << setw(width) << "��������" << setw(width)
					<< "�����" << endl << endl;

				logs = ParkingService::getLogs(username);
				for (auto log : logs)
					cout << log.getId() << setw(width) << log.getAction() << setw(width)
					<< username << endl << endl;
				cout << endl;

				cin >> e;
				break;
			}
			
			break;

		case 5:
			system("cls");
			cout << endl << "�������������/�������������� ������������..." << endl << endl;

			while (true)
			{
				cin.ignore(32767, '\n');
				cout << "������� ��� ������������: ";
				getline(cin, username);

				client = ParkingService::getClient(username);
				if (client.getId() == -1)
				{
					cout << endl << "�������� ������. ������ �����? (1)" << endl;
					if (CheckInput::check_exit_choice()) break;
					cout << endl;

					continue;
				}

				client.banUnban();
				ParkingService::editClient(client);

				cout << "�������� ���� ������� �����������!" << endl;
				cin >> e;
				break;
			}
			
			break;

		case 6:
			system("cls");
			cout << "�������� �������������� ��������..." << endl;
			cout << "����������: ��� �� ������ ��������, �����������..." << endl << endl;

			while (true)
			{
				string vehicle_price, electric_price, max_slots;

				cin.ignore(32767, '\n');
				cout << "������� ���� �������� �����������: ";
				getline(cin, vehicle_price);
				cout << "������� ���� �������� ���������� ���� ����������: ";
				getline(cin, electric_price);
				cout << "������� ������������ ���������� ����������� ����: ";
				getline(cin, max_slots);

				bool result = ParkingService::changeParkingProperties(vehicle_price, electric_price, max_slots);
				if (result)
				{
					cout << endl << "�������� ���� ������� �����������!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "�������� ������. ������ �����? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 7:
			system("cls");
			cout << "�������� ���� ������������..." << endl;

			while (true)
			{
				string username;
				cin.ignore(32767, '\n');
				cout << "������� ��� ������������: ";
				getline(cin, username);

				bool result = ParkingService::editRole(username);
				if (result)
				{
					cout << endl << "�������� ���� ������� �����������!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "�������� ������. ������ �����? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 8:
			return;

		default:
			cout << endl << "�������� ������, �����o����� ��� ���." << endl;
		}
	}
}

void Terminal::ClientMenu(Client client)
{
	while (true)
	{
		system("cls");
		cout << "������, " << client.getUsername() << "!" << endl;

		if (client.isBanned())
		{
			cout << "�� ���� ��������!" << endl;
			char e; cin >> e;
			return;
		}

		cout << "�������� �������� ��������:" << endl <<
				"1 �������� ������ ����������" << endl <<
				"2 �������� ���������" << endl <<
				"3 ������� ���������" << endl <<
				"4 �������� ���� �������" << endl <<
				"5 �������� ���������� � ����" << endl <<	
				"6 �������� ���� ������" << endl <<
				"7 ������ �����" << endl <<
				"8 �������� � �������" << endl <<
				"9 �����" << endl << endl;

		int choice = CheckInput::check_choice(1, 9);

		int width = 20;
		char e;
		vector<pair<Transport, string>> transport;
		vector<Ticket> tickets;
		double price;

		switch (choice)
		{
		case 1:
			system("cls");
			cout << "������ ����������..." << endl << endl;

			cout << "���" << setw(width) << "�����" << setw(width)
				 << "������" << endl << endl;

			transport = ParkingService::getClientTransport(client.getUsername());
			for (auto element : transport)
				cout << element.second << setw(width) << element.first.getPlateNumber() << setw(width)
					 << ((element.first.isActive()) ? "��������" : "����������") << endl;
			cout << endl;

			cin >> e;
			break;

		case 2:
			system("cls");
			cout << "�������� ������..." << endl << endl;

			AddTransport(client);

			break;

		case 3:
			system("cls");
			cout << "������� ������..." << endl << endl;

			while (true)
			{
				string plateNumber;

				cin.ignore(32767, '\n');
				cout << "������� ����� ����������: ";
				getline(cin, plateNumber);

				bool result = ParkingService::deleteTransport(plateNumber);
				if (result)
				{
					cout << endl << "�������� ���� ������� �����������!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "�������� ������. ������ �����? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 4:
			system("cls");
			cout << "�������� ���� �������..." << endl << endl;

			cout << "Id: " << setw(width) << client.getId() << endl
				<< "Name: " << setw(width) << client.getName() << endl
				<< "Username: " << setw(width - 4) << client.getUsername() << endl
				<< "Phone: " << setw(width) << client.getPhoneNumber() << endl;

			cin >> e;
			break;

		case 5:
			system("cls");
			cout << "�������� ���������� � ����..." << endl << endl;
			cout << "����������: ��� �� ������ ��������, �����������..." << endl << endl;

			while (true)
			{
				string username, password, first_name, last_name, phone_number;

				cin.ignore(32767, '\n');
				cout << "������� �����: ";
				getline(cin, username);
				cout << "������� ������: ";
				getline(cin, password);
				cout << "������� ���� ���: ";
				getline(cin, first_name);
				cout << "������� ���� �������: ";
				getline(cin, last_name);
				cout << "������� ��� ����� ��������: ";
				getline(cin, phone_number);

				Client result = ParkingService::editClient(client.getId(), username, password, first_name, last_name, phone_number);
				if (result.getId() != -1)
				{
					client = result;

					cout << endl << "�������� ���� ������� �����������!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "�������� ������. ������ �����? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 6:
			system("cls");
			cout << "�������� ���� ������..." << endl << endl;


			cout << "����� ������" << setw(2 * width - 5) << "����� ����������" << setw(width)
				<< "������" << endl << endl;

			tickets = ParkingService::getClientTickets(client.getId());
			for (auto ticket : tickets)
				cout << ticket.getStartTime() << setw(width) << ParkingService::getTransport(ticket.getTransportId()).getPlateNumber()
					 << setw(width + 10) << ((ticket.isPayed()) ? "�������" : "�� �������") << endl;
			cout << endl;

			cin >> e;
			break;

		case 7:
			system("cls");
			cout << "������ �����..." << endl << endl;

			while (true)
			{
				string plateNumber;

				cin.ignore(32767, '\n');
				cout << "������� ����� ����������: ";
				getline(cin, plateNumber);

				bool result = ParkingService::Occupate(client.getId(), plateNumber);
				if (result)
				{
					cout << endl << "�������� ���� ������� �����������!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "�������� ������. ������ �����? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 8:
			system("cls");
			cout << "�������� � �������..." << endl << endl;

			price = ParkingService::getPrice(client.getId());

			if (price == -1)
			{
				cout << "��� ��������� ����������!" << endl;
				cin >> e;
				break;
			}

			cout << "����� ����� = " << price << endl << endl;

			while (true)
			{
				cout << "������ ��������? (1)" << endl;
				cin.ignore(32767, '\n');
				if (CheckInput::check_exit_choice())
				{
					ParkingService::Pay(client.getId());
					cout << endl << "�������� ���� ������� �����������!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "�������� ������. ������ �����? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 9:
			return;

		default:
			cout << endl << "�������� ������, �����o����� ��� ���." << endl;
		}
	}
}

void Terminal::AddTransport(Client client)
{
	system("cls");

	while (true)
	{
		string plate_number, type;
		int battery;

		cin.ignore(32767, '\n');

		cout << "������� ����� ������: ";
		getline(cin, plate_number);

		cout << "������� ��� (car, motorbike, lorry, electric): ";
		getline(cin, type);

		bool result = false;

		if (type == "electric")
		{
			cout << "������� ������� ��������: ";
			cin >> battery;

			result = client.addTransport(plate_number, "Electric", battery);
		}
		else if (type == "car")
		{
			result = client.addTransport(plate_number, "Car");
		}
		else if (type == "motorbike")
		{
			result = client.addTransport(plate_number, "Motorbike");
		}
		else if (type == "lorry")
		{
			result = client.addTransport(plate_number, "Lorry");
		}
		else
		{
			cout << endl << "�������� ������. ������ �����? (1)" << endl;
			if (CheckInput::check_exit_choice()) break;
			cout << endl;
		}

		if (!result)
		{
			cout << endl << "�������� ������. ������ �����? (1)" << endl;
			if (CheckInput::check_exit_choice()) break;
			cout << endl;
		}

		cout << "�������� ���� ������� �����������!" << endl;
		char e; cin >> e;
		return;
	}
}