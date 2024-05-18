#include "auxiliaryСommands.hpp"

#include <vector>

bool ayupov::isOdd(const Polygon& polygon)
{
    return polygon.points.size() % 2;
}
bool ayupov::isEven(const Polygon& polygon)
{
    return !polygon.points.size() % 2;
}
