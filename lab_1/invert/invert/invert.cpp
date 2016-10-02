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
double GetMinor(const Matrix &, const int &, const int &);
void MakeInverseMatrix(const Matrix &, const double &);
void PrintMatrix(const Matrix &);

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

	MakeInverseMatrix(srcMatrix, determinant);
	return 0;
}

void ReadMatrixFromFile(ifstream & matrixFile, Matrix & matrix)
{
	for (int i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		for (int j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
		{
			matrixFile >> matrix[i][j];
		}
	}
}

double GetDeterminant(const Matrix & matrix)
{
	double determinant = 0;
	const int row = 0;
	short sign = 1;

	for (int col = 0; col < 3; ++col)
	{
		determinant += sign * matrix[row][col] * GetMinor(matrix, row, col);
		sign *= -1;
	}

	return determinant;
}

double GetMinor(const Matrix & matrix, const int & row, const int & col)
{
	double minorElem[4];
	int currElem = 0;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if ((i != row) && (j != col))
			{
				minorElem[currElem] = matrix[i][j];
				++currElem;
			}
		}
	}

	return (minorElem[0] * minorElem[3]) - (minorElem[1] * minorElem[2]);
}

void MakeInverseMatrix(const Matrix & srcMatrix, const double & determinant)
{

}

void PrintMatrix(const Matrix & matrix)
{
	for (int i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		for (int j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
		{
			cout << matrix[i][j];
		}
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