#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#define MAX_NUM_OF_ARG 5

using namespace std;

void CheckArgCount(int);
void CheckInputFile(ifstream &, string);
void CheckOutputFile(ofstream &, string);
void CheckStrNotEmpty(string);
void CheckWritingData(ofstream &);
void ReplaceInFiles(ifstream &, ofstream &, char * []);
void ReplaceStrToStrInLine(string &, string, string);


int main(int argc, char * argv[])
{
	CheckArgCount(argc);

	ifstream input(argv[1]);
	CheckInputFile(input, argv[1]);

	ofstream output(argv[2]);
	CheckOutputFile(output, argv[2]);

	CheckStrNotEmpty(argv[3]);

	ReplaceInFiles(input, output, argv);

	CheckWritingData(output);

	return 0;
}

void CheckArgCount(int argc)
{
	if (argc != MAX_NUM_OF_ARG)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		exit(1);
	}
}

void CheckInputFile(ifstream & input, string fileName)
{
	if (!input.is_open())
	{
		cout << "Failed to open " << fileName << " for reading\n";
		exit(1);
	}
}

void CheckOutputFile(ofstream & output, string fileName)
{
	if (!output.is_open())
	{
		cout << "Failed to open " << fileName << " for writing\n";
		exit(1);
	}
}

void CheckStrNotEmpty(string searchStr)
{
	if (searchStr == "")
	{
		cout << "Failed to search empty string\n";
		exit(1);
	}
}

void CheckWritingData(ofstream & output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		exit(1);
	}
}

void ReplaceInFiles(ifstream & input, ofstream & output, char * argv[])
{
	const string searchString  = argv[3];
	const string replaceString = argv[4];

	string currString;

	while (getline(input, currString))
	{
		ReplaceStrToStrInLine(currString, searchString, replaceString);
		output << currString << "\n";
	}
}

void ReplaceStrToStrInLine(string & currString, string searchString, string replaceString)
{
	const int replaceStringLen = replaceString.length();
	const int searchStringLen = searchString.length();

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
}
