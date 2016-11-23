#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(CPoint const & leftTop, double width, double height, std::string const& outlineColor, std::string const & fillColor)
	: ISolidShape("Rectangle")
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	m_rightBottom = CPoint(leftTop.GetX() + width, leftTop.GetY() + height);
}

double CRectangle::GetWidth() const
{
	return m_width;
};

double CRectangle::GetHeight() const
{
	return m_height;
};

CPoint const & CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint const & CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
};

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
};


double CRectangle::GetArea() const
{
	return m_width * m_height;
};

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
};

void CRectangle::AppendProperties(std::ostream & strm) const
{
	strm << "  Width = " << m_width
		<< "  Height = " << m_height
		<< "  FillColor = " << GetFillColor();
}