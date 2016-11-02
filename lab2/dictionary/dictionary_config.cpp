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
		std::string first = "";
		if (str.find(' ') != std::string::npos)
		{
			first.append(str, 0, str.find(' '));
		}

		std::string second = "";
		second.append(str, str.find(' '));

		result.emplace(first, second);
	}

	return result;
}