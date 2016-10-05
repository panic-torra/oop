#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <iomanip>

const int MAX_NUM_OF_ARG = 2;
const size_t SIZE_OF_MATRIX = 3;
const double EPS = 0.0001;

using namespace std;

typedef array < array <double, SIZE_OF_MATRIX>, SIZE_OF_MATRIX> Matrix;

bool IsFileEmpty(ifstream&);
bool TryToReadMatrixFromFile(ifstream&, Matrix&);
double GetMinor2x2(const Matrix&, const size_t, const size_t);
double GetDeterminant(const Matrix&);
bool TryToMakeInverseMatrix(const Matrix&, Matrix&);
void PrintMatrix(const Matrix&);

int main(int argc, char* argv[])
{
    if (argc != MAX_NUM_OF_ARG)
    {
        cout << "Invalid arguments count" << endl
            << "Usage: invert.exe <matrix.txt>" << endl;
        return EXIT_FAILURE;
    }
    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading.";
        return EXIT_FAILURE;
    }
    if (IsFileEmpty(input))
    {
        cout << argv[1] << " is empty.";
        return EXIT_FAILURE;
    }

	Matrix srcMatrix;
	if (!TryToReadMatrixFromFile(input, srcMatrix))
	{
		cout << "There isn`t matrix 3x3 in file." << endl;
		return EXIT_FAILURE;
	};

	Matrix dstMatrix;
	if (!TryToMakeInverseMatrix(srcMatrix, dstMatrix))
	{
		cout << "The determinant of the matrix is 0, so the inverse matrix does not exist." << endl;
		return EXIT_FAILURE;
	}
	PrintMatrix(dstMatrix);

    return EXIT_SUCCESS;
}


bool IsFileEmpty(ifstream& file)
{
	return file.peek() == ifstream::traits_type::eof();
}

bool TryToReadMatrixFromFile(ifstream& matrixFile, Matrix& matrix)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			if (matrixFile.eof())
			{
				return false;
			}
			matrixFile >> matrix[i][j];
		}
	}

	return true;
}

bool TryToMakeInverseMatrix(const Matrix& srcMatrix, Matrix& dstMatrix)
{
	double determinant = GetDeterminant(srcMatrix);
	if (fabs(determinant - 0) < EPS)
	{
		return false;
	}

	short sign = 1;
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			dstMatrix[j][i] = sign * (1 / determinant) * GetMinor2x2(srcMatrix, i, j);
			sign *= -1;
		}
	}

	return true;
}

double GetDeterminant(const Matrix& matrix)
{
	double determinant = 0;
	const size_t i = 0;
	short sign = 1;

	for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
	{
		determinant += sign * matrix[i][j] * GetMinor2x2(matrix, i, j);
		sign *= -1;
	}
	return determinant;
}

double GetMinor2x2(const Matrix& matrix, const size_t row, const size_t col)
{
	array <double, 4> minorElems;
	size_t currElem = 0;

	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		if (i == row)
		{
			continue;
		}
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			if (j == col)
			{
				continue;
			}
			minorElems[currElem] = (matrix[i][j]);
			++currElem;
		}
	}

	return (minorElems[0] * minorElems[3]) - (minorElems[1] * minorElems[2]);
}

void PrintMatrix(const Matrix& matrix)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			cout << fixed << setprecision(3) << matrix[i][j] << ' ';
		}
		cout << endl;
	}
}