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

	BOOST_AUTO_TEST_SUITE(when_engine_is_turned_off)

		BOOST_AUTO_TEST_CASE(cannot_select_gear_when_engine_turned_off)
		{
			BOOST_CHECK(!car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::NEUTRAL));

			BOOST_CHECK(!car.SetGear(Gear::FIRST));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::NEUTRAL));

			BOOST_CHECK(!car.SetGear(Gear::REVERSE));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::NEUTRAL));
		}

		BOOST_AUTO_TEST_CASE(can_be_turned_on)
		{
			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.IsEngineTurnOn());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_engine_turned_on_ : CarFixture
	{
		when_engine_turned_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_engine_turned_on, when_engine_turned_on_)
		BOOST_AUTO_TEST_CASE(cannot_be_turned_on_twice)
		{
			BOOST_CHECK(!car.TurnOnEngine());
			BOOST_CHECK(car.IsEngineTurnOn());
		}

		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			BOOST_CHECK(car.TurnOffEngine());
			BOOST_CHECK(!car.IsEngineTurnOn());
		}

		BOOST_AUTO_TEST_CASE(cannot_be_turned_off_when_speed_is_not_equal_to_zero)
		{
			BOOST_CHECK(car.SetGear(Gear::FIRST));
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(car.IsEngineTurnOn());
		}

		BOOST_AUTO_TEST_CASE(cannot_be_turned_off_twice)
		{
			BOOST_CHECK(car.TurnOffEngine());
			BOOST_CHECK(!car.IsEngineTurnOn());
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(!car.IsEngineTurnOn());
		}

		BOOST_AUTO_TEST_CASE(can_change_gear_from_neutral)
		{
			BOOST_CHECK(car.SetGear(Gear::FIRST));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::FIRST));

			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.SetGear(Gear::FIRST));
			BOOST_CHECK(car.SetSpeed(30));

			BOOST_CHECK(car.SetGear(Gear::SECOND));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::SECOND));
			BOOST_CHECK(car.SetSpeed(20));

			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.SetSpeed(0));
			BOOST_CHECK(car.SetGear(Gear::REVERSE));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::REVERSE));
		}

		BOOST_AUTO_TEST_CASE(cannot_change_gear_when_speed_is_out_of_range)
		{
			BOOST_CHECK(!car.SetGear(Gear::SECOND));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::NEUTRAL));

			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.SetGear(Gear::FIRST));
			BOOST_CHECK(car.SetSpeed(10));

			BOOST_CHECK(!car.SetGear(Gear::SECOND));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::FIRST));

			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(!car.SetGear(Gear::REVERSE));
			BOOST_CHECK_EQUAL(car.GetGear(), static_cast<int>(Gear::NEUTRAL));
		}

		BOOST_AUTO_TEST_CASE(can_change_gear_and_speed_when_selected_reverse_gear)
		{
			BOOST_CHECK(car.SetGear(Gear::REVERSE));
			BOOST_CHECK(car.SetSpeed(15));
			BOOST_CHECK_EQUAL(car.GetDirection(), static_cast<int>(Direction::BACKWARD));

			BOOST_CHECK(!car.SetGear(Gear::FIRST));
			BOOST_CHECK(car.SetSpeed(0));

			BOOST_CHECK(car.SetGear(Gear::FIRST));
			BOOST_CHECK(car.SetSpeed(15));
			BOOST_CHECK_EQUAL(car.GetDirection(), static_cast<int>(Direction::FORWARD));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()