#include "stdafx.h"
#include "IShape.h"
#include "CControl.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

using namespace std;
using namespace std::placeholders;

CControl::CControl(std::istream & input, std::ostream & output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "line", bind(&CControl::CreateLine, this, std::placeholders::_1, std::placeholders::_2) },
		{ "rectangle", bind(&CControl::CreateRectangle, this, std::placeholders::_1, std::placeholders::_2) },
		{ "triangle", bind(&CControl::CreateTriangle, this, std::placeholders::_1, std::placeholders::_2) },
		{ "circle", bind(&CControl::CreateCircle, this, std::placeholders::_1, std::placeholders::_2) }
})
{
}

bool CControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	std::shared_ptr<IShape> shape;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm, shape);
		m_shapes.push_back(shape);
	}

	return true;
}

void CControl::PrintInfo() const
{
	for (auto shape : m_shapes)
	{
		m_output << shape->ToString() << "\n";
	}
	m_output << "Shape with max area: \n"
		<< GetMaxAreaShape(m_shapes)->ToString() << "\n";
	m_output << "Shape with max perimeter: \n"
		<< GetMinPerimeterShape(m_shapes)->ToString() << "\n";
}

bool CControl::CreateLine(std::istream & args, std::shared_ptr<IShape> &shape)
{
	std::shared_ptr<CLineSegment> line;
	if (args >> line)
	{
		shape = line;
		return true;
	}
	return false;
}

bool CControl::CreateTriangle(std::istream & args, std::shared_ptr<IShape> &shape)
{
	std::shared_ptr<CTriangle> triangle;
	if (args >> triangle)
	{
		shape = triangle;
		return true;
	}
	return false;
}

bool CControl::CreateRectangle(std::istream & args, std::shared_ptr<IShape> &shape)
{
	std::shared_ptr<CRectangle> rectangle;
	if (args >> rectangle)
	{
		shape = rectangle;
		return true;
	}
	return false;
}

bool CControl::CreateCircle(std::istream & args, std::shared_ptr<IShape> &shape)
{
	std::shared_ptr<CCircle> circle;
	if (args >> circle)
	{
		shape = circle;
		return true;
	}
	return false;
}

std::shared_ptr<IShape> CControl::GetMaxAreaShape(std::vector<std::shared_ptr<IShape>> const& shapes) const
{
	return (shapes.empty()) ? nullptr : *std::max_element(shapes.begin(), shapes.end(),
		[&](std::shared_ptr<IShape> const& shape1, std::shared_ptr<IShape> const& shape2)
	{
		return shape1->GetArea() < shape2->GetArea();
	});
}

std::shared_ptr<IShape> CControl::GetMinPerimeterShape(std::vector<std::shared_ptr<IShape>> const& shapes) const
{
	return (shapes.empty()) ? nullptr : *std::min_element(shapes.begin(), shapes.end(),
		[&](std::shared_ptr<IShape> const& shape1, std::shared_ptr<IShape> const& shape2)
	{
		return shape1->GetPerimeter() > shape2->GetPerimeter();
	});
}