#include "Functors.hpp"
#include <math.h>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Geometry.hpp"

double petrov::AccPolygonAreaPart::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}
bool petrov::EqualPol::operator()(const Polygon& p1, const Polygon& p2)
{
  return p1 == mask && p1 == p2;
}
