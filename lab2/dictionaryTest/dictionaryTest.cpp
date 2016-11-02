#include "stdafx.h"
#include "../dictionary/dictionary_config.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GetDictionaryFromFile_function)

	BOOST_AUTO_TEST_CASE(return_empty_dictionary_if_fileName_is_not_correct)
	{
		const Dictionary expectedResult = {};
		stringstream input;
		Dictionary result = GetDictionaryFromFile(input);
		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(make_one_pair_in_map_by_value_in_file)
	{
		const Dictionary expectedResult = { 
			{"cat", "кошка"}
		};
		stringstream input;
		input << "cat кошка" << endl;
		Dictionary result = GetDictionaryFromFile(input);
		for (auto it = result.begin(); it != result.end(); it++)
			cout << it->first << ' ' << it->second << endl;

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(make_pairs_in_map_by_value_in_file)
	{
		const Dictionary expectedResult = {
			{ "cat", "кошка" },
			{ "cheese", "сыр" }
		};
		stringstream input;
		input << "cat кошка" << endl << "cheese сыр";
		Dictionary result = GetDictionaryFromFile(input);
		for (auto it = result.begin(); it != result.end(); it++)
			cout << it->first << ' ' << it->second << endl;

		BOOST_CHECK(result == expectedResult);
	}
BOOST_AUTO_TEST_SUITE_END()
