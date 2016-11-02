#include "stdafx.h"
#include "dictionary_config.h"

const int MAX_NUM_OF_ARG = 2;

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: dictionary.exe <input.txt>" << endl;
		return EXIT_FAILURE;
	}

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input(argv[1]);
	Dictionary dictionary = GetDictionaryFromFile(input);
	
	WorkWithDictionary(dixtionary);

	return EXIT_SUCCESS;
}