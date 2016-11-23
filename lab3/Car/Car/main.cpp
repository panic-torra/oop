#include "stdafx.h"
#include "Car.h"
#include "CarControl.h"

int main()
{
	setlocale(LC_ALL, "rus");
	CCar car;
	CCarControl virtualControl(car, std::cin, std::cout);

	while (!std::cin.fail())
	{
		std::cout << "> ";
		if (!virtualControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return EXIT_SUCCESS;
}