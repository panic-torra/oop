#include "stdafx.h"
#include "../html_decode/htmlDecode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Test_function)

	BOOST_AUTO_TEST_CASE(for_replacing_in_empty_str)
	{
		const string expectedResult = "";
		string input = "";
		const string searchStr = "a";
		const string replaceStr = "bb";
		auto result = ReplaceInStr(input, searchStr, replaceStr);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_replacing_in_str_searchStr_bigger)
	{
		const string expectedResult = "123LOOK5";
		string input = "12312312345";
		const string searchStr = "1231234";
		const string replaceStr = "LOOK";
		auto result = ReplaceInStr(input, searchStr, replaceStr);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_replacing_in_str_replaceStr_bigger)
	{
		const string expectedResult = "NO ONE'll think, \"How'd I get here, sitting next to NO ONE?\"";
		string input = "you'll think, \"How'd I get here, sitting next to you?\"";
		const string searchStr = "you";
		const string replaceStr = "NO ONE";
		auto result = ReplaceInStr(input, searchStr, replaceStr);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_replacing_in_html_without_needed)
	{
		const string expectedResult = "you'll think, \"How'd I get here, sitting next to you?\"";
		string input = "you'll think, \"How'd I get here, sitting next to you?\"";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_replacing_in_html)
	{
		const string expectedResult = "Cat <says> \"Meow\". M&M's";
		string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()
