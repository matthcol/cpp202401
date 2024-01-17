#include "Circle.h"

#include <format>
#include <numbers>

Circle::Circle(const std::string& name, std::shared_ptr<Point> center, double radius):
    Form(name), m_center(center), m_radius(radius)
{
}

std::string Circle::toString() const
{
    return std::format("{0}<c:{1}, r:{2}>", name(), m_center->toString(), m_radius);
}

void Circle::translate(double deltaX, double deltaY)
{
    m_center->translate(deltaX, deltaY);
}

double Circle::perimeter() const
{
    return 2 * std::numbers::pi * m_radius;
}

double Circle::surface() const
{
    return std::numbers::pi * m_radius * m_radius;
}

std::shared_ptr<Point> Circle::center() const
{
    return m_center;
}

void Circle::setCenter(std::shared_ptr<Point> center)
{
    m_center = center;
}

double Circle::radius() const
{
    return m_radius;
}

void Circle::setRadius(double radius)
{
    m_radius = radius;
}
