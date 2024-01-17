#include "Polygon.h"

#include <format>
#include <numeric>

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
    auto prevSummit = *m_summits.crbegin(); // last summit
    double res = 0.0;
    for (auto currentSummit : m_summits) {
        res += currentSummit->distance(*prevSummit);
        prevSummit = currentSummit;
    }
    return res;
}

double Polygon::surface() const
{
    // TODO
    return 0.0;
}
