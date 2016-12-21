#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"

struct PointFixture
{
	CPoint point;
	PointFixture()
		:point( 15, 8)
	{}
};

BOOST_FIXTURE_TEST_SUITE(CPoint_, PointFixture)

	BOOST_AUTO_TEST_CASE(creates_with_coordinats)
	{
		BOOST_CHECK_EQUAL(point.GetX(), 15);
		BOOST_CHECK_EQUAL(point.GetY(), 8);
	}
	
	BOOST_AUTO_TEST_CASE(can_be_read_from_istream)
	{
		std::stringstream input;
		input << "5 42";
		CPoint newPoint;
		BOOST_CHECK(input >> newPoint);
		BOOST_CHECK_EQUAL(newPoint.GetX(), 5);
		BOOST_CHECK_EQUAL(newPoint.GetY(), 42);
	}

BOOST_AUTO_TEST_SUITE_END()