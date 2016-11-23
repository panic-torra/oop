#pragma once

#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3,
		std::string const & outlineColor, std::string const & fillColor);
	virtual ~CTriangle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;

	CPoint const & GetVertex1() const;
	CPoint const & GetVertex2() const;
	CPoint const & GetVertex3() const;

protected:
	void AppendProperties(std::ostream & strm) const override;

private:
	CPoint m_vertices[3] = {};
	std::string m_outlineColor;
	std::string m_fillColor;
};
