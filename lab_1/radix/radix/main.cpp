#include <iostream>
#include <fstream>
#include <string>

const int MAX_NUM_OF_ARG = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

using namespace std;

bool CheckRadix(string& radix);
int StringToInt(const string str, bool& wasError);
string IntToString(const int num);
int CharToDigit(const char ch);
char DigitToChar(const int digit);
void ReverseString(string& str);
string convertValueFromSrcRadixToDstRadix(const string& srcRadix, const string&  dstRadix, int value);
int convertValueToDec(const string& srcRadix, int& value);
int convertValueTo(const string& dstRadix, int& value);


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
	if (!(CheckRadix(srcRadix)) || !(CheckRadix(dstRadix)))
	{
		cout << "Invalid radix\n"
			<< "Radix in [2; 36]\n";
		return 1;
	}

	const string value = argv[3];
	if (srcRadix == dstRadix)
	{
		cout << value << "\n";
		return 1;
	}

	bool wasError = false;
	int srcNum = StringToInt(value, wasError);
	if (wasError)
	{
		cout << "Overflow: |value| > max integer\n";
		return 1;
	}

	cout << convertValueFromSrcRadixToDstRadix(srcRadix, dstRadix, srcNum) << "\n";
	return 0;
}

string convertValueFromSrcRadixToDstRadix(const string& srcRadix, const string&  dstRadix, int value)
{
	int tmpValue = convertValueToDec(srcRadix, value);
	//value = convertValueTo(dstRadix, tmpValue);
	return IntToString(tmpValue);
}

int convertValueToDec(const string& srcRadix, int& value)
{
	bool wasError = false;
	int result = 0;
	int num = 1;
	int base = StringToInt(srcRadix, wasError);
	string str = IntToString(value);
	if (!wasError)
	{
		for (unsigned i = 0; i < str.length(); ++i)
		{
			num = (int)pow(base, str.length() - i - 1);
			result += CharToDigit(str[i]) * num;
			cout << str[i] << endl;
		}
	}
	return result;
}

int convertValueTo(const string& dstRadix, int& value)
{
	return value;
}

int StringToInt(const string str, bool& wasError)
{
	int result = 0;
	int digit = 0;
	for (size_t i = 0; i < str.length(); ++i)
	{
		digit = CharToDigit(str[i]);
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
		result = (int) ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		result = (int) ch - 'A' + 10;
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
	for (size_t i = 0; i < str.length() / 2; ++i)
	{
		swap(str[i], str[str.length() - i - 1]);
	}
}

bool CheckRadix(string& radix)
{
	return (stoi(radix) >= MIN_RADIX) && (stoi(radix) <= MAX_RADIX);
}