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
		: carControl(car, input, output)
	{
	}

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
		VerifyCommandHandling("Unknown_command", "Unknown command!");
	}

	
BOOST_AUTO_TEST_SUITE_END()