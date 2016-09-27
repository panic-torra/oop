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
int TryToReplaceInFiles(char * []);
void ReplaceStrToStrInLine(string &, const string &, const string &);

int main(int argc, char * argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	return TryToReplaceInFiles(argv);
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

int TryToReplaceInFiles(char * argv[])
{
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
	if (CheckStrNotEmpty(argv[3]))
	{
		cout << "Failed to search empty string\n";
		return 1;
	}

	const string searchStr  = argv[3];
	const string replaceStr = argv[4];
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
	const int replaceStrLen = replaceStr.length();
	const int searchStrLen = searchStr.length();
	const int currStrLen = currStr.length();

	size_t lastCopiedPos = 0;
	size_t currPos = currStr.find(searchStr, 0);
	string resultStr = "";

	while ((currPos != string::npos) || (lastCopiedPos != currStrLen))
	{
		if (currPos == lastCopiedPos)
		{
			resultStr += replaceStr;
			currPos = currStr.find(searchStr, currPos + searchStrLen);
			lastCopiedPos += searchStrLen;
		}
		else
		{
			resultStr += currStr[lastCopiedPos];
			++lastCopiedPos;
		}
	}
	currStr = resultStr;
}