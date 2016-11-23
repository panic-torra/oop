#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"
#include "../GeometricShapes/CRectangle.h"
#include "PointTest.h"

struct RectangleFixture
{
	CRectangle rectangle;
	RectangleFixture()
		:rectangle({ 0, 0 }, 20, 30, "#123456", "#00ff00")
	{}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)

	BOOST_AUTO_TEST_SUITE(creates)
		BOOST_AUTO_TEST_CASE(with_a_perimeter)
		{
			BOOST_CHECK_EQUAL(rectangle.GetPerimeter(), 100);
		}

		BOOST_AUTO_TEST_CASE(with_an_area)
		{
			BOOST_CHECK_EQUAL(rectangle.GetArea(), 20 * 30);
		}

		BOOST_AUTO_TEST_CASE(with_left_top)
		{
			IsPointsEqual(rectangle.GetLeftTop(), { 0, 0 });
		}
		BOOST_AUTO_TEST_CASE(with_right_bottom)
		{
			IsPointsEqual(rectangle.GetRightBottom(), { 20, 30 });
		}
		BOOST_AUTO_TEST_CASE(with_width)
		{
			BOOST_CHECK_EQUAL(rectangle.GetWidth(), 20);
		}
		BOOST_AUTO_TEST_CASE(with_height)
		{
			BOOST_CHECK_EQUAL(rectangle.GetHeight(), 30);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetFillColor(), "#00ff00");
	}

	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), "#123456");
	}

	BOOST_AUTO_TEST_CASE(can_print_info)
	{
		BOOST_CHECK_EQUAL(rectangle.ToString(), "Rectangle:   S = 600  P = 100  ColorOutline = #123456  Width = 20  Height = 30  FillColor = #00ff00");
	}

BOOST_AUTO_TEST_SUITE_END()
