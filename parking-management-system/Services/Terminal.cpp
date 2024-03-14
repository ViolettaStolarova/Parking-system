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

		cout << "Введите логин: ";
		getline(cin, username);

		cout << "Введите пароль: ";
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
		
		cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;		
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
		cout << "Введите логин: ";
		getline(cin, username);
		cout << "Введите пароль: ";
		getline(cin, password);
		cout << "Введите ваше имя: ";
		getline(cin, first_name);
		cout << "Введите вашу фамилию: ";
		getline(cin, last_name);
		cout << "Введите ваш номер телефона: ";
		getline(cin, phone_number);

		Client client = ParkingService::addClient(username, password, first_name, last_name, phone_number);
		if (client.getId() != -1)
		{
			cout << "Вы успешно зарегистрировались!" << endl;
			char e; cin >> e;
			break;
		}

		cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
		if (CheckInput::check_exit_choice()) break;
		cout << endl;
	}
}

void Terminal::AdminMenu(Admin admin)
{
	while (true)
	{
		system("cls");
		cout << "Привет, " << admin.getUsername() << "!" << endl << endl;

		cout <<	"Выберите желаемое действие:" << endl <<
				"1 Смотреть список клиентов" << endl <<
				"2 Смотреть список парковочных мест" << endl <<
				"3 Смотреть действия пользователей" << endl <<
				"4 Смотреть действия определённого пользователя" << endl <<
				"5 Заблокировать/разблокировать пользователя" << endl <<
				"6 Изменить характеристики парковки" << endl <<
				"7 Изменить роль пользователя" << endl <<
				"8 Выйти" << endl << endl;

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
			cout << "Список клиентов..." << endl << endl;

			cout << "Id" << setw(width) << "Логин" 
			     << setw(width) << "Имя" << setw(width) << "Телефон" 
			     << setw(width) << "Статус" << endl << endl;
			
			clients = ParkingService::getClients();
			for (auto client : clients)
				cout << client.getId() << setw(width) << client.getUsername()
				     << setw(width) << client.getName() << setw(width) << client.getPhoneNumber()
					 << setw(width) << ((client.isBanned()) ? "Забанен" : "Не забанен") << endl;
			cout << endl;

			cin >> e;
			break;

		case 2:
			system("cls");
			cout << "Список парковочных мест..." << endl << endl;

			cout << "Id" << setw(width) << "Статус"
				 << setw(width) << "Клиент" << setw(width) << "Номер транспорта" 
				 << endl << endl;

			slots = ParkingService::getParkingLot();
			for (auto slot : slots)
				cout << slot.getId() << setw(width) << ((slot.isOccupied()) ? "Занято" : "Не занято")
					 << setw(width) << slot.getClient().getName() << setw(width)
				     << setw(width) << slot.getTransport().getPlateNumber() << endl;
			cout << endl;

			cin >> e;
			break;

		case 3:
			system("cls");
			cout << "Действия пользователей..." << endl << endl;

			cout << "Id" << setw(width) << "Действие" << setw(width) 
				 << "Логин" << endl << endl;

			logs = ParkingService::getLogs();
			for (auto log : logs)
				cout << log.getId() << setw(width) << log.getAction() << setw(width)
					 << log.getClient().getUsername() << endl;
			cout << endl;					 

			cin >> e;
			break;
			
		case 4:
			system("cls");
			cout << "Действия определённого пользователя..." << endl << endl;

			while (true)
			{
				cin.ignore(32767, '\n');
				cout << "Введите имя пользователя: ";
				getline(cin, username);

				if (ParkingService::getClient(username).getId() == -1)
				{
					cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
					if (CheckInput::check_exit_choice()) break;
					cout << endl;

					continue;
				}

				cout << "Id" << setw(width) << "Действие" << setw(width)
					<< "Логин" << endl << endl;

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
			cout << endl << "Заблокировать/разблокировать пользователя..." << endl << endl;

			while (true)
			{
				cin.ignore(32767, '\n');
				cout << "Введите имя пользователя: ";
				getline(cin, username);

				client = ParkingService::getClient(username);
				if (client.getId() == -1)
				{
					cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
					if (CheckInput::check_exit_choice()) break;
					cout << endl;

					continue;
				}

				client.banUnban();
				ParkingService::editClient(client);

				cout << "Действия были успешно произведены!" << endl;
				cin >> e;
				break;
			}
			
			break;

		case 6:
			system("cls");
			cout << "Изменить характеристики парковки..." << endl;
			cout << "Примечание: что не хотите изменять, пропускайте..." << endl << endl;

			while (true)
			{
				string vehicle_price, electric_price, max_slots;

				cin.ignore(32767, '\n');
				cout << "Введите цену парковки электрокара: ";
				getline(cin, vehicle_price);
				cout << "Введите цену парковки остального вида транспорта: ";
				getline(cin, electric_price);
				cout << "Введите максимальное количество пакровочных мест: ";
				getline(cin, max_slots);

				bool result = ParkingService::changeParkingProperties(vehicle_price, electric_price, max_slots);
				if (result)
				{
					cout << endl << "Действия были успешно произведены!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 7:
			system("cls");
			cout << "Изменить роль пользователя..." << endl;

			while (true)
			{
				string username;
				cin.ignore(32767, '\n');
				cout << "Введите имя пользователя: ";
				getline(cin, username);

				bool result = ParkingService::editRole(username);
				if (result)
				{
					cout << endl << "Действия были успешно произведены!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 8:
			return;

		default:
			cout << endl << "Неверные данные, пропрoбуйте ещё раз." << endl;
		}
	}
}

void Terminal::ClientMenu(Client client)
{
	while (true)
	{
		system("cls");
		cout << "Привет, " << client.getUsername() << "!" << endl;

		if (client.isBanned())
		{
			cout << "Вы были забанены!" << endl;
			char e; cin >> e;
			return;
		}

		cout << "Выберите желаемое действие:" << endl <<
				"1 Смотреть список транспорта" << endl <<
				"2 Добавить транспорт" << endl <<
				"3 Удалить транспорт" << endl <<
				"4 Смотреть свой профиль" << endl <<
				"5 Изменить информацию о себе" << endl <<	
				"6 Смотреть свои талоны" << endl <<
				"7 Занять место" << endl <<
				"8 Оплатить и выехать" << endl <<
				"9 Выйти" << endl << endl;

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
			cout << "Список транспорта..." << endl << endl;

			cout << "Тип" << setw(width) << "Номер" << setw(width)
				 << "Статус" << endl << endl;

			transport = ParkingService::getClientTransport(client.getUsername());
			for (auto element : transport)
				cout << element.second << setw(width) << element.first.getPlateNumber() << setw(width)
					 << ((element.first.isActive()) ? "Активный" : "Неактивный") << endl;
			cout << endl;

			cin >> e;
			break;

		case 2:
			system("cls");
			cout << "Добавить машину..." << endl << endl;

			AddTransport(client);

			break;

		case 3:
			system("cls");
			cout << "Удалить машину..." << endl << endl;

			while (true)
			{
				string plateNumber;

				cin.ignore(32767, '\n');
				cout << "Введите номер транспорта: ";
				getline(cin, plateNumber);

				bool result = ParkingService::deleteTransport(plateNumber);
				if (result)
				{
					cout << endl << "Действия были успешно произведены!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 4:
			system("cls");
			cout << "Смотреть свой профиль..." << endl << endl;

			cout << "Id: " << setw(width) << client.getId() << endl
				<< "Name: " << setw(width) << client.getName() << endl
				<< "Username: " << setw(width - 4) << client.getUsername() << endl
				<< "Phone: " << setw(width) << client.getPhoneNumber() << endl;

			cin >> e;
			break;

		case 5:
			system("cls");
			cout << "Изменить информацию о себе..." << endl << endl;
			cout << "Примечание: что не хотите изменять, пропускайте..." << endl << endl;

			while (true)
			{
				string username, password, first_name, last_name, phone_number;

				cin.ignore(32767, '\n');
				cout << "Введите логин: ";
				getline(cin, username);
				cout << "Введите пароль: ";
				getline(cin, password);
				cout << "Введите ваше имя: ";
				getline(cin, first_name);
				cout << "Введите вашу фамилию: ";
				getline(cin, last_name);
				cout << "Введите ваш номер телефона: ";
				getline(cin, phone_number);

				Client result = ParkingService::editClient(client.getId(), username, password, first_name, last_name, phone_number);
				if (result.getId() != -1)
				{
					client = result;

					cout << endl << "Действия были успешно произведены!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 6:
			system("cls");
			cout << "Смотреть свои талоны..." << endl << endl;


			cout << "Время начала" << setw(2 * width - 5) << "Номер транспорта" << setw(width)
				<< "Статус" << endl << endl;

			tickets = ParkingService::getClientTickets(client.getId());
			for (auto ticket : tickets)
				cout << ticket.getStartTime() << setw(width) << ParkingService::getTransport(ticket.getTransportId()).getPlateNumber()
					 << setw(width + 10) << ((ticket.isPayed()) ? "Оплачен" : "Не оплачен") << endl;
			cout << endl;

			cin >> e;
			break;

		case 7:
			system("cls");
			cout << "Занять место..." << endl << endl;

			while (true)
			{
				string plateNumber;

				cin.ignore(32767, '\n');
				cout << "Введите номер транспорта: ";
				getline(cin, plateNumber);

				bool result = ParkingService::Occupate(client.getId(), plateNumber);
				if (result)
				{
					cout << endl << "Действия были успешно произведены!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 8:
			system("cls");
			cout << "Оплатить и выехать..." << endl << endl;

			price = ParkingService::getPrice(client.getId());

			if (price == -1)
			{
				cout << "Нет активного транспорта!" << endl;
				cin >> e;
				break;
			}

			cout << "Общая сумма = " << price << endl << endl;

			while (true)
			{
				cout << "Хотите оплатить? (1)" << endl;
				cin.ignore(32767, '\n');
				if (CheckInput::check_exit_choice())
				{
					ParkingService::Pay(client.getId());
					cout << endl << "Действия были успешно произведены!" << endl;
					cin >> e;
					break;
				}

				cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
				if (CheckInput::check_exit_choice()) break;
				cout << endl;
			}

			break;

		case 9:
			return;

		default:
			cout << endl << "Неверные данные, пропрoбуйте ещё раз." << endl;
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

		cout << "Введите номер машины: ";
		getline(cin, plate_number);

		cout << "Введите тип (car, motorbike, lorry, electric): ";
		getline(cin, type);

		bool result = false;

		if (type == "electric")
		{
			cout << "Введите ёмкость баттареи: ";
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
			cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
			if (CheckInput::check_exit_choice()) break;
			cout << endl;
		}

		if (!result)
		{
			cout << endl << "Неверные данные. Хотите выйти? (1)" << endl;
			if (CheckInput::check_exit_choice()) break;
			cout << endl;
		}

		cout << "Действия были успешно произведены!" << endl;
		char e; cin >> e;
		return;
	}
}