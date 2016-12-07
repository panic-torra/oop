#include "stdafx.h"
#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint & start, const CPoint & end, const std::string & outlineColor)
	: IShape("line")
	, m_startPoint(start)
	, m_endPoint(end)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return std::hypot(m_endPoint.GetX() - m_startPoint.GetX(), m_endPoint.GetY() - m_startPoint.GetY());
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

void CLineSegment::AppendProperties(std::ostream & strm) const
{
}

bool operator >> (std::istream & input, std::shared_ptr<CLineSegment> & line)
{
	CPoint start;
	CPoint end;
	std::string outlineColor;
	if (input >> start && input >> end && input >> outlineColor)
	{
		line = std::make_shared<CLineSegment>(start, end, outlineColor);
		return true;
	}
	return false;
}