#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM_OF_ARG 5

using namespace std;

bool CheckArgCount(int);
bool CheckInputFile(ifstream &);
bool CheckOutputFile(ofstream &);
bool CheckStrNotEmpty(const string &);
bool CheckWritingData(ofstream &);
void ReplaceInFiles(ifstream &, ofstream &, char * []);
void ReplaceStrToStrInLine(string &, const string &, const string &);

int main(int argc, char * argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
	ifstream input(argv[1]);
	if (CheckInputFile(input))
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}
	ofstream output(argv[2]);
	if (CheckOutputFile(output))
	{
		cout << "Failed to open " << argv[1] << " for writeng\n";
		return 1;
	}
	if (CheckStrNotEmpty(argv[3]))
	{
		cout << "Failed to search empty string\n";
		return 1;
	}

	ReplaceInFiles(input, output, argv);
	CheckWritingData(output);

	return 0;
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

bool CheckStrNotEmpty(const string & searchStr)
{
	return (searchStr == "");
}

bool CheckWritingData(ofstream & output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		throw 1;
	}
}

void ReplaceInFiles(ifstream & input, ofstream & output, char * argv[])
{
	const string searchStr  = argv[3];
	const string replaceStr = argv[4];

	string currString;

	while (getline(input, currString))
	{
		ReplaceStrToStrInLine(currString, searchStr, replaceStr);
		output << currString << "\n";
	}
}

void ReplaceStrToStrInLine(string & currString, const string & searchStr, const string & replaceStr)
{
	const int replaceStrLen = replaceStr.length();
	const int searchStrLen = searchStr.length();

	size_t currPos = 0;
	size_t lastPos = 0;

	while (currPos != string::npos)
	{
		currPos = currString.find(searchStr, lastPos);
		if (currPos != string::npos)
		{
			currString.replace(currPos, searchStrLen, replaceStr);
			lastPos = currPos + replaceStrLen;
		}
	}
}