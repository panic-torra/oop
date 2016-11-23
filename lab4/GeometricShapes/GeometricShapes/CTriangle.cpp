#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint & point1, const CPoint & point2, const CPoint & point3,
	const std::string & outlineColor, const std::string & fillColor)
	:m_vertices({ point1, point2, point3 })
{
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

CPoint const & CTriangle::GetVertex1() const
{
	return m_vertices[0];
}

CPoint const & CTriangle::GetVertex2() const
{
	return m_vertices[1];
}

CPoint const & CTriangle::GetVertex3() const
{
	return m_vertices[2];
}

double CTriangle::GetPerimeter() const
{
	return std::hypot(m_vertices[0].GetX() - m_vertices[1].GetX(), m_vertices[0].GetY() - m_vertices[1].GetY())
		+ std::hypot(m_vertices[1].GetX() - m_vertices[2].GetX(), m_vertices[1].GetY() - m_vertices[2].GetY())
		+ std::hypot(m_vertices[2].GetX() - m_vertices[0].GetX(), m_vertices[2].GetY() - m_vertices[0].GetY());
}

double CTriangle::GetArea() const
{
	auto semiperimetr = GetPerimeter() / 2;
	auto sideA = std::hypot(m_vertices[0].GetX() - m_vertices[1].GetX(), m_vertices[0].GetY() - m_vertices[1].GetY());
	auto sideB = std::hypot(m_vertices[1].GetX() - m_vertices[2].GetX(), m_vertices[1].GetY() - m_vertices[2].GetY());
	auto sideC = std::hypot(m_vertices[2].GetX() - m_vertices[0].GetX(), m_vertices[2].GetY() - m_vertices[0].GetY());
	return sqrt(semiperimetr * (semiperimetr - sideA) * (semiperimetr - sideB) * (semiperimetr - sideC));
}


std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

void CTriangle::AppendProperties(std::ostream & strm) const
{
	strm << "  FillColor = " << GetFillColor();
}