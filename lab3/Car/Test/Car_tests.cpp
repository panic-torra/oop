#include "stdafx.h"

#include "../Car/Car.h"
#include <boost/function.hpp>

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_CASE(engine_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
	}

	BOOST_AUTO_TEST_CASE(speed_is_zero_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(gear_is_neutral_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::NEUTRAL));
	}

	BOOST_AUTO_TEST_CASE(direction_is_stop_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetDirection(), static_cast<int>(Direction::NONE));
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_off_when_gear_is_neutral)
	{
		BOOST_CHECK(car.TurnOffEngine());
	}

BOOST_AUTO_TEST_SUITE_END()