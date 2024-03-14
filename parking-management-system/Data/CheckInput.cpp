#include "CheckInput.h"

int CheckInput::check_choice(int a, int b)
{
	while (true)
	{
		int choice;
		std::cin >> choice;

		if (std::cin.fail() || std::cin.peek() != '\n' || choice < a || choice > b)
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Неверные данные, пропрoбуйте ещё раз." << std::endl;
		}
		else
		{
			return choice;
		}
	}
}

bool CheckInput::check_exit_choice()
{
	char choice;
	choice = getchar();

	if (std::cin.fail() || std::cin.peek() != '\n' || choice != '1')
	{
		std::cin.clear();
		return false;
	}

	return true;
}