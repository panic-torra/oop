#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"
#include "../GeometricShapes/CCircle.h"
#include "PointTest.h"
#define _USE_MATH_DEFINES
#include <math.h>

struct CircleFixture
{
	CCircle circle;
	CircleFixture()
		:circle({ 0, 0 }, 20, "#123456", "#00ff00")
	{}
};

BOOST_FIXTURE_TEST_SUITE(Circle, CircleFixture)

	BOOST_AUTO_TEST_SUITE(creates)
		BOOST_AUTO_TEST_CASE(with_a_perimeter)
		{
			BOOST_CHECK_CLOSE(circle.GetPerimeter(), 2 * M_PI * 20, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_an_area)
		{
			BOOST_CHECK_CLOSE(circle.GetArea(), M_PI * 20 * 20, 0.001);
		}

		BOOST_AUTO_TEST_CASE(with_center)
		{
			IsPointsEqual(circle.GetCenter(), { 0, 0 });
		}
		BOOST_AUTO_TEST_CASE(with_radius)
		{
			BOOST_CHECK_EQUAL(circle.GetRadius(), 20);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK_EQUAL(circle.GetFillColor(), "#00ff00");
	}

	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(circle.GetOutlineColor(), "#123456");
	}

	BOOST_AUTO_TEST_CASE(can_print_info)
	{
		BOOST_CHECK_EQUAL(circle.ToString(), "Circle:   S = 1256.64  P = 125.664  ColorOutline = #123456  Radius = 20  FillColor = #00ff00");
	}

BOOST_AUTO_TEST_SUITE_END()
