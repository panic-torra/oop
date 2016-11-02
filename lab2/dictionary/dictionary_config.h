#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>

typedef std::map <std::string, std::string> Dictionary;

Dictionary GetDictionaryFromFile(std::istream & file);