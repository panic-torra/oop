#pragma once

class IShape
{
public:
	IShape(std::string const& type);
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string GetOutlineColor() const = 0;
	std::string ToString() const;

protected:
	virtual void AppendProperties(std::ostream & strm) const = 0;
private:
	std::string m_type;
};