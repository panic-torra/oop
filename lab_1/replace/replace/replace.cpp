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
int TryToReplaceInFile(const string &, const string &, const string &, const string &);
void ReplaceStrToStrInLine(string &, const string &, const string &);

int main(int argc, char * argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	return TryToReplaceInFile(argv[1], argv[2], argv[3], argv[4]);
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

int TryToReplaceInFile(const string & inputFileName, const string & outputFileName, const string & searchStr, const string & replaceStr)
{
	ifstream input(inputFileName);
	if (CheckInputFile(input))
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return 1;
	}
	ofstream output(outputFileName);
	if (CheckOutputFile(output))
	{
		cout << "Failed to open " << outputFileName << " for writeng\n";
		return 1;
	}
	if (CheckStrNotEmpty(searchStr))
	{
		cout << "Failed to search empty string\n";
		return 1;
	}

	string currStr;

	while (getline(input, currStr))
	{
		ReplaceStrToStrInLine(currStr, searchStr, replaceStr);
		output << currStr << "\n";
	}

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}

void ReplaceStrToStrInLine(string & currStr, const string & searchStr, const string & replaceStr)
{
	const size_t replaceStrLen = replaceStr.length();
	const size_t searchStrLen = searchStr.length();
	const size_t currStrLen = currStr.length();

	size_t lastCopiedPos = 0;
	size_t currPos = currStr.find(searchStr, 0);
	string resultStr;

	while (currPos != string::npos)
	{
		resultStr.append(currStr, lastCopiedPos , currPos - lastCopiedPos);
		resultStr += replaceStr;
		lastCopiedPos = currPos + searchStrLen;
		currPos = currStr.find(searchStr, lastCopiedPos);
	}
	if (lastCopiedPos != currStrLen)
	{
		resultStr.append(currStr, lastCopiedPos);
	}
	currStr = resultStr;
} 