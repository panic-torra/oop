#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

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
	vector<double> nums;
	copy(istream_iterator<double>(input), istream_iterator<double>(),
		back_inserter(nums));

	cout << nums[0] << ", " << nums[1];
}