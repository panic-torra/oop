#pragma once

#include "IShape.h"
#include "�Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint & start, const CPoint & end, const std::string & outlineColor);
	~CLineSegment() = default;

	double GetArea() const;
	double GetPerimeter() const override;
	std::string ToString() const;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	std::string GetOutlineColor() const;

protected:
	void AppendProperties(std::ostream & strm) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	std::string m_outlineColor;
};