#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM_OF_ARG 4

using namespace std;

bool CheckArgCount(int);
string convertValueFromSrcRadixToDstRadix(const string &, const string &, const string &);

int main(int argc, char* argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: radix.exe <source radix> <destination radix> <value>\n";
		return 1;
	}

    const string srcRadix = argv[1];
	const string dstRadix = argv[2];
	const string value = argv[3];

	cout << convertValueFromSrcRadixToDstRadix(srcRadix, dstRadix, value) << "\n";
	return 0;
}

bool CheckArgCount(int argc)
{
	return (argc != MAX_NUM_OF_ARG);
}

string convertValueFromSrcRadixToDstRadix(const string & srcRadix, const string &  dstRadix, const string &  value)
{

}