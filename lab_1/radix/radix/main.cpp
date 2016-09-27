#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM_OF_ARG 3

using namespace std;

bool CheckArgCount(int);
bool CheckInputFile(ifstream &);
bool CheckOutputFile(ofstream &);
bool CheckArgNotEmpty(const string &);

int main(int argc, char* argv[])
{
	CheckArgCount(argc);

	ifstream input(argv[1]);
	if (CheckInputFile(input))
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}
	ofstream output(argv[2]);
	if (CheckOutputFile(output))
	{
		cout << "Failed to open " << argv[2] << " for writeng\n";
		return 1;
	}
	if (CheckArgNotEmpty(argv[3]))
	{
		cout << "Failed to work with empty string. Expected number.\n";
		return 1;
	}

}

bool CheckArgCount(int argc)
{
	return (argc != MAX_NUM_OF_ARG);
}

bool CheckInputFile(ifstream & input)
{
	return (!input.is_open());
}

bool CheckOutputFile(ofstream & output)
{
	return (!output.is_open());
}

bool CheckArgNotEmpty(const string & arg)
{
	return (arg == "");
}