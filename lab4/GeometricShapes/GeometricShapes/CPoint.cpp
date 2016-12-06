#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{
}

std::string CPoint::ToString() const
{
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

bool operator >> (std::istream & input, CPoint & point)
{
	if (input >> point.m_x && input >> point.m_y)
	{
		return true;
	}
	return false;
}