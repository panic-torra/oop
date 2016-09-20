#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CheckArgCount(int);
void CheckInputFile(ifstream);
void CheckOutputFile(ifstream);
void CheckSearchStr(string);
void ReplaceStringToStringInFile(ifstream, string, string);

int main(int argc, char * argv[])
{
	CheckArgCount(argc);

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	const string searchString  = argv[3];

	if (searchString.length() == 0)
	{
		cout << "Failed to search empty string\n";
		return 1;
	}

	const string replaceString = argv[4];
	const int replaceStringLen = replaceString.length();
	const int searchStringLen = searchString.length();
	string currString;

	while (getline(input, currString))
	{
		size_t currPosition = 0;
		size_t lastPosition = 0;
		while (currPosition != string::npos)
		{
			currPosition = currString.find(searchString, lastPosition);
			if (currPosition != string::npos)
			{
				currString.replace(currPosition, searchStringLen, replaceString);
				lastPosition = currPosition + replaceStringLen;
			}

		}
		output << currString << "\n";
	}

	if (!output.flush())
	{
	    cout << "Failed to save data on disk\n";
	    return 1;
	}

	return 0;
}

void CheckArgCount(int argc)
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		exit(1);
	}
}
