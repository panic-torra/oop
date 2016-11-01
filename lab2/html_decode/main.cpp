#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "htmlDecode.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: html_decode.exe <input.txt>" << endl;
		return EXIT_FAILURE;
	}
	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading.";
		return EXIT_FAILURE;
	}

	string htmlStr = "";
	while (getline(input, htmlStr))
	{
		cout << HtmlDecode(htmlStr) << "\n";
	}

	return EXIT_SUCCESS;
}