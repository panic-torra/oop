#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"

void IsPointsEqual(CPoint left, CPoint right)
{
	BOOST_CHECK_CLOSE(left.GetX(), right.GetX(), 0.00001);
	BOOST_CHECK_CLOSE(left.GetY(), right.GetY(), 0.00001);
}