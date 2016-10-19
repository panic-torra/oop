#include "stdafx.h"
#include <iostream>
#include "primeNums.h"

const int MAX_NUM_OF_ARG = 2;

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != MAX_NUM_OF_ARG)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: primeNumbers.exe <upperBound>" << endl;
		return EXIT_FAILURE;
	}

	int upperBound = atoi(argv[1]);
	if ((upperBound <= 0) || (upperBound > 100000000))
	{
		cout << "Invalid argument" << endl
			<< "Upper bound in [1, 100000000]" << endl;
		return EXIT_FAILURE;
	}

	set<int> prime = GeneratePrimeNumbersSet(upperBound);

	cout << prime.size() << endl;
	return EXIT_SUCCESS;
}