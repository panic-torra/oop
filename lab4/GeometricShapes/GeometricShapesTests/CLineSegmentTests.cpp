#include "stdafx.h"
#include "../GeometricShapes/CLineSegment.h"
#include "PointTest.h"

struct LineSegmentFixture
{
	CLineSegment line;
	LineSegmentFixture()
		:line({ 0, 15 }, { 15, 7 }, "#000000")
	{}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment_creates, LineSegmentFixture)

	BOOST_AUTO_TEST_CASE(with_outline_color)
	{
		BOOST_CHECK_EQUAL(line.GetOutlineColor(), "#000000");
	}
	BOOST_AUTO_TEST_CASE(with_area_equal_to_zero)
	{
		BOOST_CHECK_EQUAL(line.GetArea(), 0);
	}
	BOOST_AUTO_TEST_CASE(with_perimeter)
	{
		BOOST_CHECK_EQUAL(line.GetPerimeter(), 17);
	}
	BOOST_AUTO_TEST_CASE(with_start_point)
	{
		IsPointsEqual(line.GetStartPoint(), { 0, 15 });
	}
	BOOST_AUTO_TEST_CASE(with_end_point)
	{
		IsPointsEqual(line.GetEndPoint(), { 15, 7 });
	}

BOOST_AUTO_TEST_SUITE_END()