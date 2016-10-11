#include <iostream>
#include <fstream>
#include <string>

const int MAX_NUM_OF_ARG = 2;

using namespace std;

string HtmlDecode(string const& htmlStr);
string ReplaceInStr(string const& currStr, const string searchStr, const string replaceStr);

int main(int argc, char * argv[])
{
	if (argc != MAX_NUM_OF_ARG)
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

	string htmlStr, resultStr;
	while (getline(input, htmlStr))
	{
		resultStr = HtmlDecode(htmlStr);
		cout << resultStr << "\n";
	}

	return EXIT_SUCCESS;
}

string HtmlDecode(string const& htmlStr)
{
	string resultStr = htmlStr;

	if (htmlStr.find("&quot;", 0) != string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&quot;", "\"");
	}
	if (htmlStr.find("&apos;", 0) != string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&apos;", "'");
	}
	if (htmlStr.find("&lt;", 0) != string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&lt;", "<");
	}
	if (htmlStr.find("&gt;", 0) != string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&gt;", ">");
	}
	if (htmlStr.find("&amp;", 0) != string::npos)
	{
		resultStr = ReplaceInStr(resultStr, "&amp;", "&");
	}
	
	return resultStr;
}

string ReplaceInStr(string const& currStr, const string searchStr, const string replaceStr)
{
	const size_t searchStrLen = searchStr.length();
	const size_t currStrLen = currStr.length();

	size_t lastCopiedPos = 0;
	size_t currPos = currStr.find(searchStr, 0);
	string resultStr;

	while (currPos != string::npos)
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