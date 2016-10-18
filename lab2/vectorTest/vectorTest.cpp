#include "stdafx.h"
#include "../vector/processVector.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Test_function)

	BOOST_AUTO_TEST_CASE(for_getting_str_from_file)
	{
		stringstream expectedStream;
		expectedStream << "2 5 4 3 8 75 2";
		vector<double> expectedResult;
		copy(istream_iterator<double>(expectedStream), istream_iterator<double>(),
			back_inserter(expectedResult));
		stringstream input;
		input << "2 5 4 3 8 75 2";

		auto result = GetVectorFromFile(input);
		BOOST_CHECK(result == expectedResult);
	}
BOOST_AUTO_TEST_SUITE_END()
