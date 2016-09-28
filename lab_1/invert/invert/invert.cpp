#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM_OF_ARG 2
#define NUM_OF_ROWS_IN_MATRIX 3
#define NUM_OF_COLUMNS_IN_MATRIX 3

using namespace std;

typedef double Matrix[NUM_OF_ROWS_IN_MATRIX][NUM_OF_COLUMNS_IN_MATRIX];

bool CheckArgCount(int);
bool CheckInputFile(ifstream &);
bool TryToGetInvertMatrix(ifstream &);
void ReadMatrixFromFile(ifstream &, Matrix &);
double GetDeterminant(const Matrix &);
void PrintInversMatrix(const Matrix &, const double &);

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

	return TryToGetInvertMatrix(input);
}

bool CheckArgCount(int argc)
{
	return (argc != MAX_NUM_OF_ARG);
}

bool CheckInputFile(ifstream & input)
{
	return (!input.is_open());
}

bool TryToGetInvertMatrix(ifstream & matrixFile)
{
	Matrix srcMatrix;
	ReadMatrixFromFile(matrixFile, srcMatrix);

	double determinant = GetDeterminant(srcMatrix);
	if (determinant == 0)
	{
		cout << "The determinant of the matrix is 0, so the inverse matrix does not exist." << endl;
		return 1;
	}

	PrintInversMatrix(srcMatrix, determinant);
	return 0;
}

void ReadMatrixFromFile(ifstream & matrixFile, Matrix & matrix)
{
	for (int i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		for (int j = 0; j < NUM_OF_ROWS_IN_MATRIX; ++j)
		{
			matrixFile >> matrix[i][j];
		}
	}
}

double GetDeterminant(const Matrix & matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2]
		 + matrix[0][1] * matrix[1][2] * matrix[2][0]
		 + matrix[0][2] * matrix[1][0] * matrix[2][1]
		 - matrix[0][2] * matrix[1][1] * matrix[2][0]
		 - matrix[0][0] * matrix[1][2] * matrix[2][1]
		 - matrix[0][1] * matrix[1][0] * matrix[2][2];
}

void PrintInversMatrix(const Matrix & srcMatrix, const double & determinant)
{

}