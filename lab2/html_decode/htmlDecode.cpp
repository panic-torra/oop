#include "stdafx.h"
#include <map>
#include <vector>
#include <iostream>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

std::string HtmlDecode(const std::string& htmlStr)
{
	std::string resultStr = "";
	const std::map<std::string, char> htmlSymbols = 
	{
		{ "&amp;", '&' },
		{ "&quot;", '\"' },
		{ "&apos;", '\'' },
		{ "&lt;", '<' },
		{ "&gt;", '>' }
	};

	for (size_t strPos = 0; strPos < htmlStr.length(); ++strPos)
	{
		bool wasReplace = false;
		size_t lastPos = 0;

		if (htmlStr[strPos] == '&')
		{
			for (auto iterator = htmlSymbols.begin(); iterator != htmlSymbols.end(); ++iterator)
			{
				if (htmlStr.find(iterator->first, strPos) == strPos)
				{
					resultStr += iterator->second;
					strPos += iterator->first.size() - 1;
					wasReplace = true;
				}
			}
		}

		if (!wasReplace)
		{
			resultStr += htmlStr[strPos];
		}
	}

	return resultStr;
}