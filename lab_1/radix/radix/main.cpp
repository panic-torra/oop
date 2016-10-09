#include <iostream>
#include <fstream>
#include <string>

const int MAX_NUM_OF_ARG = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

using namespace std;

bool CheckRadix(string& radix);
int StringToInt(const string& str, bool& wasError);
string IntToString(const int num);
int CharToDigit(const char ch);
char DigitToChar(const int digit);
void ReverseString(string& str);
string convertValueFromSrcRadixToDstRadix(const string& srcRadix, const string&  dstRadix, const string&  value);


int main(int argc, char* argv[])
{
	if (argc != MAX_NUM_OF_ARG)
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

string convertValueFromSrcRadixToDstRadix(const string& srcRadix, const string&  dstRadix, const string&  value)
{
	bool wasError = false;
	StringToInt(value, wasError);
	//перевести value из строки в число
	//перевести из srcRadix в десятичную
	//перевести из десятичной в dstRadix
	//перевести получившееся число в строку
	//ПЕРЕПОЛНЕНИЯ КОНТРОЛИРОВАТЬ ДЛИННОЙ АРИФМЕТИКОЙ
}

int StringToInt(const string& str, bool& wasError)
{
	int result = 0;
	for (size_t i = 0; i < str.length(); ++i)
	{
		int digit = CharToDigit(str[i]);
		if (result >(INT_MAX - digit) / 10)
		{
			wasError = true;
			return 0;
		}
		result = result * 10 + digit;
	}

	return result;
}

int CharToDigit(const char ch)
{
	int result = -1;
	if (ch >= '0' && ch <= '9')
	{
		result = ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		result = ch - 'A' + 10;
	}

	return result;
}

string IntToString(int num)
{
	string result;
	while (num != 0)
	{
		result += DigitToChar(num % 10);
		num /= 10;
	}
	ReverseString(result);

	return result;
}

char DigitToChar(const int digit)
{
	int result = '0';
	if (digit >= '0' && digit <= '9')
	{
		result = digit + '0';
	}
	else if (digit >= 'A' && digit <= 'Z')
	{
		result = digit + 'A' - 10;
	}

	return result;
}

void ReverseString(string& str)
{

}

bool CheckRadix(string& radix)
{
	return (stoi(radix) >= MIN_RADIX) && (stoi(radix) <= MAX_RADIX);
}