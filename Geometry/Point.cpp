#include "Point.h"

Point::Point(const std::string& name, double x, double y): Form(name), m_x(x), m_y(y)
{
}

void Point::setX(double x)
{
	m_x = x;
}

double Point::x() const
{
	return m_x;
}

void Point::setY(double y)
{
	m_y = y;
}

double Point::y() const
{
	return m_y;
}
