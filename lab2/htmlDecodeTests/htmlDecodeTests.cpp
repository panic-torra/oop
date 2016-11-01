#include "stdafx.h"
#include "../html_decode/htmlDecode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

	BOOST_AUTO_TEST_CASE(doesnt_spoil_string)
	{
		const string expectedResult = "The quick brown fox jumps over the lazy dog";
		string input = "The quick brown fox jumps over the lazy dog";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(replace_required_substrings_once)
	{
		const string expectedResult = "Cat <says> \"Meow. M&M's";
		string input = "Cat &lt;says&gt; &quot;Meow. M&amp;M&apos;s";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(replace_required_repeated_substrings)
	{
		const string expectedResult = "Cat <says> \"Meow\". M&M's\\\ Cat <says> \"Meow\".";
		string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\\\ Cat &lt;says&gt; &quot;Meow&quot;.";
		auto result = HtmlDecode(input);

		BOOST_CHECK(result == expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()
