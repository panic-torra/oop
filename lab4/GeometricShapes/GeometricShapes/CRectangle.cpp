#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(CPoint const & leftTop, double width, double height, std::string const & outlineColor, std::string const & fillColor)
	: ISolidShape("Rectangle")
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
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

bool operator >> (std::istream & input, std::shared_ptr<CRectangle> & rectangle)
{
	CPoint leftTop;
	float width;
	float height;
	std::string outlineColor;
	std::string fillColor;
	if (input >> leftTop && input >> width && input >> height && input >> outlineColor && input >> fillColor)
	{
		rectangle = std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
		return true;
	}
	return false;
}