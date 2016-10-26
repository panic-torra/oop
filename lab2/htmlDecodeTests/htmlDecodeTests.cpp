#include "stdafx.h"
#include "../html_decode/htmlDecode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ReplaseInStr_function)

	BOOST_AUTO_TEST_CASE(handle_empty_string)
	{
		const string expectedResult = "";
		string input = "";
		const string searchStr = "a";
		const string replaceStr = "bb";
		auto result = ReplaceInStr(input, searchStr, replaceStr);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(replace_string_bigger_than_searching)
	{
		const string expectedResult = "The quick br!!wn f!!x jumps !!ver the lazy d!!g";
		string input = "The quick brown fox jumps over the lazy dog";
		const string searchStr = "o";
		const string replaceStr = "!!";
		auto result = ReplaceInStr(input, searchStr, replaceStr);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(replace_string_smaller_than_searching)
	{
		const string expectedResult = "The quick red fox jumps over the lazy dog";
		string input = "The quick brown fox jumps over the lazy dog";
		const string searchStr = "brown";
		const string replaceStr = "red";
		auto result = ReplaceInStr(input, searchStr, replaceStr);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

	BOOST_AUTO_TEST_CASE(doesnt_spoil_string)
	{
		const string expectedResult = "The quick brown fox jumps over the lazy dog";
		string input = "The quick brown fox jumps over the lazy dog";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(replace_needed_substrings)
	{
		const string expectedResult = "Cat <says> \"Meow\". M&M's";
		string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()
