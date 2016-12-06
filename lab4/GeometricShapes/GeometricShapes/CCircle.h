#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint const & center, double radius, std::string const & outlineColor, std::string const & fillColor);
	virtual ~CCircle() = default;
	double GetArea() const;
	double GetPerimeter() const;
	std::string GetOutlineColor() const;
	std::string GetFillColor() const;

	CPoint const& GetCenter() const;
	double GetRadius() const;

protected:
	void AppendProperties(std::ostream & strm) const override;

private:
	CPoint m_center;
	double m_radius = 0;
	std::string m_outlineColor;
	std::string m_fillColor;
};

bool operator >> (std::istream & input, std::shared_ptr<CCircle> & circle);