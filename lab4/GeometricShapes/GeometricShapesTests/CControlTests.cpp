#include "stdafx.h"
#include "../GeometricShapes/IShape.h"
#include "../GeometricShapes/CControl.h"


struct ShapesControlDependencies
{
	CControl control;
	std::stringstream input;
	std::stringstream output;
	std::stringstream expectedStr;
	ShapesControlDependencies()
		:control(input, output)
	{}
};

BOOST_FIXTURE_TEST_SUITE(CControl_, ShapesControlDependencies)
	BOOST_AUTO_TEST_CASE(handle_line_segment)
	{
		input << "line 2 195 20 300 #000";
		BOOST_CHECK(control.HandleCommand());
		control.PrintInfo();
		expectedStr << "line:   S = 0  P = 106.532  ColorOutline = #000\n"
			<< "Shape with max area:\n"
			<<  "line:   S = 0  P = 106.532  ColorOutline = #000\n"
			<<  "Shape with max perimeter:\n"
			<<  "line:   S = 0  P = 106.532  ColorOutline = #000\n";
		BOOST_CHECK_EQUAL(output.str(), expectedStr.str());
	}

	BOOST_AUTO_TEST_CASE(handle_incorrect_line)
	{
		input << "";
		BOOST_CHECK(!control.HandleCommand());
		input << "something stupid";
		BOOST_CHECK(!control.HandleCommand());
		input << "circle 2 300";
		BOOST_CHECK(!control.HandleCommand());
		expectedStr << "";
		BOOST_CHECK_EQUAL(output.str(), expectedStr.str());
	}

	BOOST_AUTO_TEST_CASE(handle_circle_shape)
	{
		input << "circle 0 0 20 #300 #000\n"
			<< "line 0 0 0 300 #000";
		BOOST_CHECK(control.HandleCommand());
		BOOST_CHECK(control.HandleCommand());
		control.PrintInfo();
		expectedStr << "Circle:   S = 1256.64  P = 125.664  ColorOutline = #300  Radius = 20  FillColor = #000\n"
			<< "line:   S = 0  P = 300  ColorOutline = #000\n"
			<< "Shape with max area:\n"
			<< "Circle:   S = 1256.64  P = 125.664  ColorOutline = #300  Radius = 20  FillColor = #000\n"
			<< "Shape with max perimeter:\n"
			<< "line:   S = 0  P = 300  ColorOutline = #000\n";
		BOOST_CHECK_EQUAL(output.str(), expectedStr.str());
	}

	BOOST_AUTO_TEST_CASE(handle_rectangle_shape)
	{
		input << "circle 0 0 20 #300 #000\n"
			<< "line 0 0 0 300 #000\n"
			<< "rectangle 120 456 15 70 #000 #aabbcc";
		BOOST_CHECK(control.HandleCommand());
		BOOST_CHECK(control.HandleCommand());
		BOOST_CHECK(control.HandleCommand());
		control.PrintInfo();
		expectedStr << "Circle:   S = 1256.64  P = 125.664  ColorOutline = #300  Radius = 20  FillColor = #000\n"
			<< "line:   S = 0  P = 300  ColorOutline = #000\n"
			<< "Rectangle:   S = 1050  P = 170  ColorOutline = #000  Width = 15  Height = 70  FillColor = #aabbcc\n"
			<< "Shape with max area:\n"
			<< "Circle:   S = 1256.64  P = 125.664  ColorOutline = #300  Radius = 20  FillColor = #000\n"
			<< "Shape with max perimeter:\n"
			<< "line:   S = 0  P = 300  ColorOutline = #000\n";
		BOOST_CHECK_EQUAL(output.str(), expectedStr.str());
	}


BOOST_AUTO_TEST_SUITE_END()