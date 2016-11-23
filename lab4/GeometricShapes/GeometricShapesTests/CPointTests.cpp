#include "stdafx.h"
//#include "../GeometricShapes/ÑPoint.h"

void IsPointsEqual(CPoint left, CPoint right)
{
	BOOST_CHECK_CLOSE(left.GetX(), right.GetX(), 0.00001);
	BOOST_CHECK_CLOSE(left.GetY(), right.GetY(), 0.00001);
}

BOOST_AUTO_TEST_SUITE(CPoint)

	BOOST_AUTO_TEST_CASE(inits_by_zeroes)
	{
		CPoint point;
		IsPointsEqual(point, { 0, 0 });
	}

	BOOST_AUTO_TEST_CASE(can_be_set_by_current_values)
	{
		CPoint point(5, 17);
		IsPointsEqual(point, { 5, 17 });
	}
BOOST_AUTO_TEST_SUITE_END()