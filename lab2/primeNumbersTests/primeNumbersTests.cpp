#include "stdafx.h"
#include "..\primeNumbers\primeNums.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(InitVectorOfPrimes_function)

	BOOST_AUTO_TEST_CASE(generate_empty_vector)
	{
		vector<bool> expectedResult{};
		auto result = InitVectorOfPrimes(0);

		BOOST_CHECK(result == expectedResult);
	}
	
	BOOST_AUTO_TEST_CASE(generate_vector_of_10_primes)
	{
		vector<bool> expectedResult{ 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0};
		auto result = InitVectorOfPrimes(10);

		BOOST_CHECK(result == expectedResult);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)
	BOOST_AUTO_TEST_CASE(generate_empty_set)
	{
		set<int> expectedResult{};
		auto result = GeneratePrimeNumbersSet(1);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(generate_set_more_than_max)
	{
		set<int> expectedResult{};
		auto result = GeneratePrimeNumbersSet(100000001);

		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(generate_set_of_500_primes)
	{
		auto expectedResult = 500;
		auto result = GeneratePrimeNumbersSet(3571);

		BOOST_CHECK(result.size() == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(generate_max_size_set)
	{
		auto expectedResult = 5761455;
		auto result = GeneratePrimeNumbersSet(100000000);

		BOOST_CHECK(result.size() == expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()