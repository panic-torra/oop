#include "stdafx.h"
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)


std::string ReplaceInStr(std::string const& currStr, std::string const searchStr, std::string const replaceStr)
{
	const size_t searchStrLen = searchStr.length();
	const size_t currStrLen = currStr.length();

	size_t lastCopiedPos = 0;
	size_t currPos = currStr.find(searchStr, 0);
	std::string resultStr;

	while (currPos != std::string::npos)
	{
		resultStr.append(currStr, lastCopiedPos, currPos - lastCopiedPos);
		resultStr += replaceStr;
		lastCopiedPos = currPos + searchStrLen;
		currPos = currStr.find(searchStr, lastCopiedPos);
	}
	if (lastCopiedPos != currStrLen)
	{
		resultStr.append(currStr, lastCopiedPos);
	}
	return resultStr;
}

std::string HtmlDecode(std::string const& htmlStr)
{
	std::string resultStr = htmlStr;

	if (htmlStr.find("&quot;", 0) != std::string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&quot;", "\"");
	}
	if (htmlStr.find("&apos;", 0) != std::string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&apos;", "'");
	}
	if (htmlStr.find("&lt;", 0) != std::string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&lt;", "<");
	}
	if (htmlStr.find("&gt;", 0) != std::string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&gt;", ">");
	}
	if (htmlStr.find("&amp;", 0) != std::string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&amp;", "&");
	}

	return resultStr;
}