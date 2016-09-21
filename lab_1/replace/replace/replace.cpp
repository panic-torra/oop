#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM_OF_ARG 5

using namespace std;

void CheckArgCount(int);
void CheckInputFile(ifstream &, const string &);
void CheckOutputFile(ofstream &, const string &);
void CheckStrNotEmpty(const string &);
void CheckWritingData(ofstream &);
void ReplaceInFiles(ifstream &, ofstream &, char * []);
void ReplaceStrToStrInLine(string &, const string &, const string &);

int main(int argc, char * argv[])
{
	ifstream input(argv[1]);
	ofstream output(argv[2]);
	try
	{
		CheckArgCount(argc);
		CheckInputFile(input, argv[1]);
		CheckOutputFile(output, argv[2]);
		CheckStrNotEmpty(argv[3]);
	}
	catch (int)
	{
		return 1;
	}
	
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
		throw 1;
	}
}

void CheckInputFile(ifstream & input, const string  & fileName)
{
	if (!input.is_open())
	{
		cout << "Failed to open " << fileName << " for reading\n";
		throw 1;
	}
}

void CheckOutputFile(ofstream & output, const string  & fileName)
{
	if (!output.is_open())
	{
		cout << "Failed to open " << fileName << " for writing\n";
		throw 1;
	}
}

void CheckStrNotEmpty(const string & searchStr)
{
	if (searchStr == "")
	{
		cout << "Failed to search empty string\n";
		throw 1;
	}
}

void CheckWritingData(ofstream & output)
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