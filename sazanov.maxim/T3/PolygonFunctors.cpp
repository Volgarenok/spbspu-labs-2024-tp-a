#include "PolygonFunctors.hpp"

double sazanov::AccumulatePolygonAreaPart::operator()(double area, const Point& second)
{
  area += (second.x - first.x) * (first.y + second.y);
  first = second;
  return area;
}
