#include "stdafx.h"
#include "../GeometricShapes/IShape.h"
#include "../GeometricShapes/CControl.h"


struct ShapesControlDependencies
{
	CControl control;
	std::stringstream input;
	std::stringstream output;
	std::string expectedStr;
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
		expectedStr = "line:    S = 0   P = 106.532  ColorOutline = #000\nShape with max area:\n" + 
			+ "line:   S = 0  P = 106.532  ColorOutline = #000\n" +
			+ "Shape with max perimeter :\n" +
			+ "line:   S = 0  P = 106.532  ColorOutline = #000\n";
		BOOST_CHECK_EQUAL(output.str(), expectedStr);
	}
	BOOST_AUTO_TEST_CASE(handle_incorrect_line_segment)
	{
		input << "line 2 195 20 300";
		BOOST_CHECK(control.HandleCommand());
		expectedStr = "line:    S = 0   P = 106.532  ColorOutline = #000";
		BOOST_CHECK_EQUAL(output.str(), expectedStr);
	}
BOOST_AUTO_TEST_SUITE_END()