#include "stdafx.h"
#include "Car.h"
#include "CarControl.h"

int main()
{
	setlocale(LC_ALL, "rus");
	CCar matiz;
	/*CCarControl virtualControl(matiz, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!virtualControl.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}*/
	return EXIT_SUCCESS;
}