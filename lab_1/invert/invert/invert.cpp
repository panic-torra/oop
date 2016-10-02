#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define MAX_NUM_OF_ARG 2
#define NUM_OF_ROWS_IN_MATRIX 3
#define NUM_OF_COLUMNS_IN_MATRIX 3
#define EPS 0.0001

using namespace std;

typedef double Matrix[NUM_OF_ROWS_IN_MATRIX][NUM_OF_COLUMNS_IN_MATRIX];

bool CheckArgCount(const short&);
bool CheckInputFile(const ifstream&);
bool IsFileEmpty(ifstream&);
bool TryToGetInvertMatrix(ifstream&);
bool TryToReadMatrixFromFile(ifstream&, Matrix&);
double GetDeterminant(const Matrix&);
double GetMinor2x2(const Matrix&, const short&, const short&);
void MakeInverseMatrix(const Matrix&, Matrix&, const double&);
void PrintMatrix(const Matrix&);

int main(int argc, char * argv[])
{
    if (CheckArgCount(argc))
    {
        cout << "Invalid arguments count" << endl
            << "Usage: invert.exe <matrix.txt>" << endl;
        return 1;
    }
    ifstream input(argv[1]);
    if (CheckInputFile(input))
    {
        cout << "Failed to open " << argv[1] << " for reading.";
        return 1;
    }
    if (IsFileEmpty(input))
    {
        cout << argv[1] << " is empty.";
        return 1;
    }

    return TryToGetInvertMatrix(input);
}

bool TryToGetInvertMatrix(ifstream& matrixFile)
{
    Matrix srcMatrix;
    Matrix dstMatrix;
    if (!TryToReadMatrixFromFile(matrixFile, srcMatrix))
    {
        cout << "There isn`t matrix 3x3 in file." << endl;
        return 1;
    };

    double determinant = GetDeterminant(srcMatrix);
    if (fabs(determinant - 0) < EPS)
    {
        cout << "The determinant of the matrix is 0, so the inverse matrix does not exist." << endl;
        return 1;
    }

    MakeInverseMatrix(srcMatrix, dstMatrix, determinant);
    PrintMatrix(dstMatrix);

    return 0;
}

bool TryToReadMatrixFromFile(ifstream& matrixFile, Matrix& matrix)
{
    for (short i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
    {
        for (short j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
        {
            if (!matrixFile.eof())
            {
                matrixFile >> matrix[i][j];
            }
            else
            {
                return 0;
            }
        }
    }

    return 1;
}

double GetDeterminant(const Matrix& matrix)
{
    double determinant = 0;
    const short i = 0;
    short sign = 1;

    for (short j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
    {
        determinant += sign * matrix[i][j] * GetMinor2x2(matrix, i, j);
        sign *= -1;
    }

    return determinant;
}

void MakeInverseMatrix(const Matrix& srcMatrix, Matrix& dstMatrix, const double& determinant)
{
    short sign = 1;
    for (short i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
    {
        for (short j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
        {
            dstMatrix[j][i] = sign * (1 / determinant) * GetMinor2x2(srcMatrix, i, j);
            sign *= -1;
        }
    }
}

double GetMinor2x2(const Matrix& matrix, const short& row, const short& col)
{
    double minorElems[4];
    short currElem = 0;

    for (short i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
    {
		if (i == row)
		{
			continue;
		}
        for (short j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
        {
			if (j == col)
			{
				continue;
			}
            minorElems[currElem] = matrix[i][j];
		    ++currElem;
        }
    }

    return (minorElems[0] * minorElems[3]) - (minorElems[1] * minorElems[2]);
}

void PrintMatrix(const Matrix& matrix)
{
    for (short i = 0; i < NUM_OF_ROWS_IN_MATRIX; ++i)
    {
        for (short j = 0; j < NUM_OF_COLUMNS_IN_MATRIX; ++j)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

bool CheckArgCount(const short& argc)
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