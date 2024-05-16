#include "operations.hpp"

double novikov::hasEvenVertexesCount(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

double novikov::hasOddVertexesCount(const Polygon& polygon)
{
  return !hasEvenVertexesCount(polygon);
}

double novikov::hasVertexesCount(const Polygon& polygon, size_t num)
{
  return polygon.points.size() == num;
}

double novikov::reverseValue(const Polygon& polygon)
{
  return 1.0 / polygon.points.size();
}
