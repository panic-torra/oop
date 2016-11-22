#include "stdafx.h"
#include "ÑPoint.h"

CPoint::CPoint(double x, double y)
	: x(x)
	, y(y)
{
}

std::string CPoint::ToString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}