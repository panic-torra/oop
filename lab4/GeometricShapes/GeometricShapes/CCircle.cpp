#include "stdafx.h"
#include "CCircle.h"
#include "ISolidShape.h"
#include "CPoint.h"

CCircle::CCircle(CPoint const & center, double radius, std::string const & outlineColor, std::string const & fillColor)
	:ISolidShape("Circle"),
	m_center(center),
	m_radius(radius),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
}

CPoint const & CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
};

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
};

double CCircle::GetArea() const
{
	return M_PI * std::pow(m_radius, 2);
};

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
};

void CCircle::AppendProperties(std::ostream & strm) const
{
	strm << "  Radius = " << m_radius
		<< "  FillColor = " << GetFillColor();
}

bool operator >> (std::istream & input, std::shared_ptr<CCircle> & circle)
{
	CPoint center;
	unsigned radius;
	std::string outlineColor;
	std::string fillColor;
	if (input >> center && input >> radius && input >> outlineColor && input >> fillColor)
	{
		circle = std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
		return true;
	}
	return false;
}