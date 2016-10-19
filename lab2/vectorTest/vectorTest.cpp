#include "stdafx.h"
#include "../vector/processVector.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Test_function)

	BOOST_AUTO_TEST_CASE(for_getting_empty_str_from_file)
	{
		vector<double> expectedResult{};
		stringstream input;
		input << "";
		auto result = GetVectorFromFile(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_getting_str_from_file)
	{
		vector<double> expectedResult{ 2, 5, 4, 3, 8, 75, 2, };
		stringstream input;
		input << "2 5 4 3 8 75 2";
		auto result = GetVectorFromFile(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_processing_string)
	{
		vector<double> expectedResult{ 6, 12, 18, 24, 30, 36 };
		vector<double> input{ 1, 2, 3, 4, 5, 6 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_processing_string_with_negative)
	{
		vector<double> expectedResult{ -100, -90, -50, -30, -20, -20, 10 };
		vector<double> input{ 5, 2, 3, 9, 2, -1, 10 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(for_processing_invalid_string)
	{
		vector<double> expectedResult{ 5, 2, 0, 9, 2, 1, 10 };
		vector<double> input{ 5, 2, 0, 9, 2, 1, 10 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}
BOOST_AUTO_TEST_SUITE_END()
