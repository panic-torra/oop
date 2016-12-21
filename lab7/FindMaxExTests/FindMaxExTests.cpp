#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx/FindMaxEx.h"
#include "CAthlete.h"

CAthlete MichaelJordan("Michael Jordan", 1.98f, 98);
CAthlete MuhammadAli("Muhammad Ali", 1.91f, 107);
CAthlete UsainBolt("Usain Bolt", 1.95f, 94);
CAthlete BabeRuth("Babe Ruth", 1.88f, 98);
		
std::vector<CAthlete> emptyVec;
std::vector<CAthlete> athletes = { MichaelJordan, MuhammadAli, UsainBolt, BabeRuth };

CAthlete maxAthlete;

BOOST_AUTO_TEST_SUITE(FindMaxEx_)

	BOOST_AUTO_TEST_CASE(can_handle_empty_vector)
	{
		BOOST_CHECK(emptyVec.empty());
		BOOST_CHECK(!FindMaxEx(emptyVec, maxAthlete, LessHeight));
		BOOST_CHECK(!FindMaxEx(emptyVec, maxAthlete, LessFullName));
	}

	BOOST_AUTO_TEST_CASE(can_find_max_athlet_by_name)
	{
		BOOST_CHECK(!athletes.empty());
		BOOST_CHECK(FindMaxEx(athletes, maxAthlete, LessFullName));
		BOOST_CHECK_EQUAL(maxAthlete.fullName, "Usain Bolt");
	}

	BOOST_AUTO_TEST_CASE(can_find_max_athlet_by_height)
	{
		BOOST_CHECK(!athletes.empty());
		BOOST_CHECK(FindMaxEx(athletes, maxAthlete, LessHeight));
		BOOST_CHECK_EQUAL(maxAthlete.height, 1.98f);
		BOOST_CHECK_EQUAL(maxAthlete.fullName, "Michael Jordan");
	}

	BOOST_AUTO_TEST_CASE(can_find_max_athlet_by_weight)
	{
		BOOST_CHECK(!athletes.empty());
		BOOST_CHECK(FindMaxEx(athletes, maxAthlete, LessWeight));
		BOOST_CHECK_EQUAL(maxAthlete.weight, 107);
		BOOST_CHECK_EQUAL(maxAthlete.fullName, "Muhammad Ali");
	}

BOOST_AUTO_TEST_SUITE_END()
