#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM_OF_ARG 2
#define NUM_OF_ROWS_IN_MATRIX 3
#define NUM_OF_COLUMNS_IN_MATRIX 3

using namespace std;

bool CheckArgCount(int);
bool CheckInputFile(ifstream &);

int main(int argc, char * argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: invert.txt <matrix.txt>\n";
		return 1;
	}
	ifstream input(argv[1]);
	if (CheckInputFile(input))
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	PrintInvertMatrix

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
