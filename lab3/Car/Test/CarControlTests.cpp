#include "stdafx.h"
#include "..\Car\Car.h"
#include "..\Car\CarControl.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

struct CarControlDependencies
{
	CCar car;
	stringstream input;
	stringstream output;
};

struct CarControlFixture : CarControlDependencies
{
	CCarControl carControl;

	CarControlFixture()
		: carControl(car, input, output){}

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(carControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(CCarController_class, CarControlFixture)

	BOOST_AUTO_TEST_CASE(handle_empty_input)
	{
		input = stringstream();
		CCarControl carController(car, input, output);
		BOOST_CHECK(!carController.HandleCommand());
	}

	BOOST_AUTO_TEST_CASE(handle_unknown_command)
	{
		input = stringstream();
		BOOST_CHECK(input << "Uknown command");
		BOOST_CHECK(!carControl.HandleCommand());
	}

	BOOST_AUTO_TEST_CASE(can_turn_on_engine)
	{
		VerifyCommandHandling("EngineOn", "Car engine was turned on\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_info_when_car_is_stopped)
	{
		car.TurnOffEngine();
		VerifyCommandHandling("Info", "Engine: off\nGear: 0\nSpeed: 0\nDirection: none\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_changed_info)
	{
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		VerifyCommandHandling(
			"Info", "Engine: on\nGear: 1\nSpeed: 20\nDirection: forward\n"
		);
	}

	BOOST_AUTO_TEST_CASE(can_print_alert_messages)
	{
		car.TurnOffEngine();
		VerifyCommandHandling(
			"SetSpeed 30", "Speed is out of range for current gear or car engine is turned off\n"
		);
	}

	BOOST_AUTO_TEST_CASE(can_show_info_that_operation_on_car_engine_is_already_done)
	{
		car.TurnOnEngine();
		VerifyCommandHandling(
			"EngineOn", "Car engine is already turned on\n"
		);

		car.TurnOffEngine();
		VerifyCommandHandling(
			"EngineOff", "Car engine is already turned off\n"
		);
	}

BOOST_AUTO_TEST_SUITE_END()