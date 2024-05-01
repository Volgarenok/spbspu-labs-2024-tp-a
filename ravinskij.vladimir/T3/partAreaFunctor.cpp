#include "partAreaFunctor.hpp"
#include <cmath>

namespace rav = ravinskij;
double rav::PartAreaFunctor::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}

