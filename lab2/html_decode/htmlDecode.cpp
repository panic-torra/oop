#include "stdafx.h"
#include <map>
#include <vector>
#include <iostream>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

namespace
{
	const std::string HTML_ENTITIES[5][2] =
	{
		{ "&amp;", "&" },
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" }
	};
}

std::string HtmlDecode(const std::string& htmlStr)
{
	std::string resultStr;
	resultStr.reserve(htmlStr.size());
	

	for (size_t strPos = 0; strPos < htmlStr.size(); ++strPos)
	{
		bool wasReplace = false;

		if (htmlStr[strPos] == '&')
		{
			for (std::string item : HTML_ENTITIES)
			{
				if (htmlStr.find(HTML_ENTITIES[i][0].c_str(), strPos, HTML_ENTITIES[i][0].length()) == strPos)
				{
					resultStr += HTML_ENTITIES[i][1];
					strPos += HTML_ENTITIES[i][0].size() - 1;
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