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

		cout << "������������!" << endl << endl <<
			"�������� �������� ��������:" << endl <<
			"1 ����� � �������" << endl <<
			"2 ������������������" << endl <<
			"3 �����" << endl << endl;


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
			cout << endl << "�������� ������, �����o����� ��� ���." << endl;
		}
	}

	return 0;
}