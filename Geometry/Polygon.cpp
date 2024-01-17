#include "Polygon.h"

#include <format>

Polygon::Polygon(const std::string& name, std::initializer_list<std::shared_ptr<Point>> summits):
    Form(name), m_summits(summits)
{
}

std::string Polygon::toString() const
{
    return std::format("{0}[{1} summits]", name(), m_summits.size());
}

void Polygon::translate(double deltaX, double deltaY)
{
}

double Polygon::perimeter() const
{
    return 0.0;
}

double Polygon::surface() const
{
    return 0.0;
}
