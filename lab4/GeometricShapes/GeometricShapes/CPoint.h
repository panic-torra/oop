#pragma once

class CPoint
{
public:
	CPoint() = default;
	CPoint(double m_x, double m_y);
	~CPoint() = default;

	std::string ToString() const;
	double GetX() const;
	double GetY() const;
private:
	double m_x = 0.0;
	double m_y = 0.0;
};