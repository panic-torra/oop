#include "stdafx.h"
#include "dictionary_config.h"

Dictionary GetDictionaryFromFile(std::istream & file)
{
	Dictionary result;
	
	if (!file.good())
	{
		return result;
	}

	std::string str;
	while (std::getline(file, str))
	{
		std::string first = std::getline(file, str);

		std::string second = "";
		second.append(str, str.find(' '));

		result.emplace(first, second);
		std::cout << first << " " << second << std::endl;
	}

	return result;
}

void WorkWithDictionary(Dictionary & dictionary)
{

}