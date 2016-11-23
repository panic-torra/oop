#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"
#include "../GeometricShapes/CTriangle.h"
#include "PointTest.h"

struct TriangleFixture_
{
	CTriangle triangle;
	TriangleFixture_()
		:triangle({ 0, 0 }, { 0, 3 }, { 4, 3 }, "#123456", "#ff2510")
	{}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture_)

	BOOST_AUTO_TEST_SUITE(creates)
		BOOST_AUTO_TEST_CASE(with_a_perimeter)
		{
			BOOST_CHECK_EQUAL(triangle.GetPerimeter(), 12);
		}

		BOOST_AUTO_TEST_CASE(with_an_area)
		{
			BOOST_CHECK_EQUAL(triangle.GetArea(), 3 * 4 * 0.5);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_CASE(can_get_vertex)
	{
		IsPointsEqual(triangle.GetVertex1(), { 0, 0 });
		IsPointsEqual(triangle.GetVertex2(), { 0, 3 });
		IsPointsEqual(triangle.GetVertex3(), { 4, 3 });
	}

	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), "#ff2510");
	}

	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), "#123456");
	}

	BOOST_AUTO_TEST_CASE(can_print_info)
	{
		BOOST_CHECK_EQUAL(triangle.ToString(), "Triangle:   S = 6  P = 12  ColorOutline = #123456  FillColor = #ff2510");
	}

BOOST_AUTO_TEST_SUITE_END()
