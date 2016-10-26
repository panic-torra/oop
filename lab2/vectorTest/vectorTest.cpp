#include "stdafx.h"
#include "../vector/processVector.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GetNumbers_function)

	BOOST_AUTO_TEST_CASE(handle_empty_string)
	{
		vector<double> expectedResult{};
		stringstream input;
		input << "";
		auto result = GetVectorFromFile(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(get_values_from_file)
	{
		vector<double> expectedResult{ 2, 5, 4, 3, 8, 75, 2, };
		stringstream input;
		input << "2 5 4 3 8 75 2";
		auto result = GetVectorFromFile(input);

		BOOST_CHECK(result == expectedResult);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProcessVector_function)
	BOOST_AUTO_TEST_CASE(handle_empty_container)
	{
		vector<double> expectedResult;
		vector<double> input;
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(doesnt_change_values_if_min_is_equal_to_zero)
	{
		vector<double> expectedResult{ 5, 2, 0, 9, 2, 1, 10 };
		vector<double> input{ 5, 2, 0, 9, 2, 1, 10 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(handle_sorted_input)
	{
		vector<double> expectedResult{ 6, 12, 18, 24, 30, 36 };
		vector<double> input{ 1, 2, 3, 4, 5, 6 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(handle_input_with_negative_values)
	{
		vector<double> expectedResult{ -50, -20, -30, -90, -20, 10, -100 };
		vector<double> input{ 5, 2, 3, 9, 2, -1, 10 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(handle_input_where_only_one_repeated_value)
	{
		vector<double> expectedResult{ 1, 1, 1, 1, 1, 1 };
		vector<double> input{ 1, 1, 1, 1, 1, 1 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(handle_classic_good_input)
	{
		vector<double> expectedResult{ 105, 30, 450, 135, 30, 225, 150, 30, 180, 45 };
		vector<double> input{ 7, 2, 30, 9, 2, 15, 10, 2, 12, 3 };
		auto result = ProcessVector(input);

		BOOST_CHECK(result == expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()