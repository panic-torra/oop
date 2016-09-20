// lab_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}


	/*
	char ch;
	// Считываем в переменную ch символ из входного потока
	// возвращаем значение, приводимое к bool, которое сигнализирует об успехе
	while (input.get(ch))
	{
	if (!output.put(ch))
	{
	cout << "Failed to save data on disk\n";
	return 1;
	}
	}

	if (!output.flush()) // Если не удалось сбросить данные на диск
	{
	cout << "Failed to save data on disk\n";
	return 1;
	}
	*/

	return 0;
}
