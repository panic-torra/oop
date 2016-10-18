#include <iostream>
#include <fstream>
#include <vector>
#include <set>

const int MAX_NUM_OF_ARG = 2;

using namespace std;

set<int> GeneratePrimeNumbersSet(unsigned int upperBound);

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

	/*for (set<int>::iterator i = prime.begin(); i != prime.end(); ++i)
	{
	cout << *i << "  ";
	}*/

	cout << "\n" << prime.size() << endl;
	return EXIT_SUCCESS;
}

set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	vector<bool> tmpSet(upperBound);

	tmpSet[0] = tmpSet[1] = true;
	for (size_t k = 3; k * k <= upperBound; ++k)
	{
		for (size_t i = 3; ((i < upperBound) && (i % k == 0) && (i != k) && (!tmpSet[i])); ++i)
		{
			tmpSet[i] = true;
		}
	}

	set<int> result;
	result.insert(2);
	for (size_t i = 3; i < upperBound; i += 2)
	{
		if (!tmpSet[i])
		{
			result.insert(i);
		}
	}

	return result;
}