#include <iostream>
#include <vector>
#include <string>

#include "Database.h"
#include "Terminal.h"
#include "CheckInput.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	Database::SeedData();

	while (true)
	{
		system("cls");

		cout << "Приветствуем!" << endl << endl <<
			"Выберете желаемое действие:" << endl <<
			"1 Войти в систему" << endl <<
			"2 Зарегистрироваться" << endl <<
			"3 Выйти" << endl << endl;


		int choice = CheckInput::check_choice(1, 3);

		switch (choice)
		{
		case 1:
			Terminal::Login();
			break;
		case 2:
			Terminal::Register();
			break;
		case 3:
			Database::SaveChanges();
			return 0;
		default:
			cout << endl << "Неверные данные, пропрoбуйте ещё раз." << endl;
		}
	}

	return 0;
}