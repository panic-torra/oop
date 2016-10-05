#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

const int MAX_NUM_OF_ARG = 2;
const size_t NUM_OF_ROWS_IN_MATRIX = 3;
const size_t NUM_OF_COLUMNS_IN_MATRIX = 3;
const double EPS = 0.0001;

using namespace std;

typedef vector<vector<double>> Matrix;

bool CheckArgCount(const int argc)
{
	return (argc != MAX_NUM_OF_ARG);
}

bool CheckInputFile(const ifstream& input)
{
	return (!input.is_open());
}

bool IsFileEmpty(ifstream& file)
{
	return file.peek() == ifstream::traits_type::eof();
}

Matrix InitMatrix()
{
	Matrix matrix(NUM_OF_ROWS_IN_MATRIX);
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
		{
			matrix[i].push_back(0);
		}
	}

	return matrix;
}

bool TryToReadMatrixFromFile(ifstream& matrixFile, Matrix& matrix)
{
	for (size_t i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		for (size_t j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
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

double GetMinor2x2(const Matrix& matrix, const size_t row, const size_t col)
{
	vector <double> minorElems;
	size_t currElem = 0;

	for (size_t i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		if (i == row)
		{
			continue;
		}
		for (size_t j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
		{
			if (j == col)
			{
				continue;
			}
			minorElems.push_back(matrix[i][j]);
			++currElem;
		}
	}

	return (minorElems[0] * minorElems[3]) - (minorElems[1] * minorElems[2]);
}

double GetDeterminant(const Matrix& matrix)
{
	double determinant = 0;
	const size_t i = 0;
	short sign = 1;

	for (size_t j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
	{
		determinant += sign * matrix[i][j] * GetMinor2x2(matrix, i, j);
		sign *= -1;
	}

	return determinant;
}

void MakeInverseMatrix(const Matrix& srcMatrix, Matrix& dstMatrix, const double determinant)
{
	short sign = 1;
	for (size_t i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		for (size_t j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
		{
			dstMatrix[j][i] = sign * (1 / determinant) * GetMinor2x2(srcMatrix, i, j);
			sign *= -1;
		}
	}
}

void PrintMatrix(const Matrix& matrix)
{
	for (size_t i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
	{
		for (size_t j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
		{
			cout << fixed << setprecision(3) << matrix[i][j] << ' ';
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
    if (CheckArgCount(argc))
    {
        cout << "Invalid arguments count" << endl
            << "Usage: invert.exe <matrix.txt>" << endl;
        return EXIT_FAILURE;
    }
    ifstream input(argv[1]);
    if (CheckInputFile(input))
    {
        cout << "Failed to open " << argv[1] << " for reading.";
        return EXIT_FAILURE;
    }
    if (IsFileEmpty(input))
    {
        cout << argv[1] << " is empty.";
        return EXIT_FAILURE;
    }

	Matrix srcMatrix = InitMatrix();
	if (!TryToReadMatrixFromFile(input, srcMatrix))
	{
		cout << "There isn`t matrix 3x3 in file." << endl;
		return EXIT_FAILURE;
	};

	double determinant = GetDeterminant(srcMatrix);
	if (fabs(determinant - 0) < EPS)
	{
		cout << "The determinant of the matrix is 0, so the inverse matrix does not exist." << endl;
		return EXIT_FAILURE;
	}

	Matrix dstMatrix = InitMatrix();
	MakeInverseMatrix(srcMatrix, dstMatrix, determinant);
	PrintMatrix(dstMatrix);

    return EXIT_SUCCESS;
}