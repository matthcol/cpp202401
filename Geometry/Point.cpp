#include "Point.h"
#include <sstream>
#include <cmath>

Point::Point():Form(), m_x(0.0), m_y(0.0)
//Point::Point():Point("", 0.0, 0.0)
{
}

Point::Point(const std::string& name, double x, double y): Form(name), m_x(x), m_y(y)
{
}

Point::~Point()
{
	std::clog << "Point destroyed:" << *this << std::endl;
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

std::string Point::toString() const
{
	// format: A(1.0, 2.4)
	std::stringstream buffer;
	buffer << name() << '(' << m_x << ", " << m_y << ')';
	return buffer.str();
}

double Point::distance(const Point& other) const
{
	return hypot(m_x - other.m_x, m_y - other.m_y);
}

bool Point::operator==(const Point& other) const
{
	return std::is_eq(*this <=> other);
}

std::partial_ordering Point::operator<=>(const Point& other) const
{
	auto cmp = m_x <=> other.m_x;
	if (cmp == std::partial_ordering::equivalent) {
		cmp = m_y <=> other.m_y;
		if (cmp == std::partial_ordering::equivalent) {
			cmp = name() <=> other.name();
		}
	}
	return cmp;
}

void Point::translate(double deltaX, double deltaY)
{
	m_x += deltaX;
	m_y += deltaY;
}
