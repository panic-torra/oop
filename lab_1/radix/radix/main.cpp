#include <iostream>
#include <fstream>
#include <string>

const int MAX_NUM_OF_ARG = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const string VALID_SYMBOLS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

using namespace std;

bool CheckArgCount(const int argc)
{
	return (argc != MAX_NUM_OF_ARG);
}

bool CheckRadix(string& radix)
{
	return (stoi(radix) >= MIN_RADIX) && (stoi(radix) <= MAX_RADIX);
}

string convertValueFromSrcRadixToDstRadix(const string& srcRadix, const string&  dstRadix, const string&  value)
{
	//перевести value из строки в число
	//перевести из srcRadix в десятичную
	//перевести из десятичной в dstRadix
	//перевести получившееся число в строку
	//ПЕРЕПОЛНЕНИЯ КОНТРОЛИРОВАТЬ ДЛИННОЙ АРИФМЕТИКОЙ
}

int StringToInt(const string& str, int radix, bool& wasError)
{
	int i;
}

string IntToString(int n, int radix, bool& wasError)
{
	int i;
}

int main(int argc, char* argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: radix.exe <source radix> <destination radix> <value>\n";
		return 1;
	}

    string srcRadix = argv[1];
	string dstRadix = argv[2];
	if ((CheckRadix(srcRadix)) || (CheckRadix(dstRadix)))
	{
		cout << "Invalid radix\n"
			<< "Radix in [2; 36]\n";
		return 1;
	}

	const string value = argv[3];

	cout << convertValueFromSrcRadixToDstRadix(srcRadix, dstRadix, value) << "\n";
	return 0;
}