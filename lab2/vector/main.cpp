#include <iostream>
#include <fstream>
#include <vector>
#include "stdafx.h"
#include "ProcessVector.h"

const int MAX_NUM_OF_ARG = 2;

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != MAX_NUM_OF_ARG)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: vector.exe <input.txt>" << endl;
		return EXIT_FAILURE;
	}
	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading.";
		return EXIT_FAILURE;
	}

	auto nums = GetVectorFromFile(input);
	auto result = ProcessVector(nums);

	if (result == nums)
	{
		cout << "Nothing changed in input:" << endl;
		copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, " "));
		return EXIT_FAILURE;
	}
	else
	{
		sort(result.begin(), result.end());
		copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	}

	return EXIT_SUCCESS;
}