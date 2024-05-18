#include "auxiliaryCommands.hpp"

#include <vector>
#include <cmath>

double ayupov::getTriangleArea::operator()(const Point& three)
{

}
bool ayupov::isOdd(const Polygon& polygon)
{
    return polygon.points.size() % 2;
}
bool ayupov::isEven(const Polygon& polygon)
{
    return !polygon.points.size() % 2;
}
