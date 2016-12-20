#pragma once
#include "stdafx.h"
#include <boost/noncopyable.hpp>

class IShape;

class CControl : boost::noncopyable
{
public:
	CControl() = default;
	CControl(std::istream &in, std::ostream &out);
	~CControl() = default;
	void HandleCommand();
	void PrintInfo() const;

private:
	bool CreateLine(std::istream & args, std::shared_ptr<IShape> &shape);
	bool CreateRectangle(std::istream & args, std::shared_ptr<IShape> &shape);
	bool CreateTriangle(std::istream & args, std::shared_ptr<IShape> &shape);
	bool CreateCircle(std::istream & args, std::shared_ptr<IShape> &shape);
	std::shared_ptr<IShape> GetMaxAreaShape(std::vector<std::shared_ptr<IShape>> const& shapes) const;
	std::shared_ptr<IShape> GetMinPerimeterShape(std::vector<std::shared_ptr<IShape>> const& shapes) const;

	std::istream & m_input;
	std::ostream & m_output;
	std::vector<std::shared_ptr<IShape>> m_shapes;

	const std::map<std::string const, std::function<bool(std::istream & args, std::shared_ptr<IShape> & shape)>> m_actionMap;
};