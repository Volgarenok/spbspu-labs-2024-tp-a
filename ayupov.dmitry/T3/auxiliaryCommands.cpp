#include "auxiliaryCommands.hpp"

#include <vector>
#include <algorithm>
#include <numeric>

double ayupov::GetTriangleArea::operator()(const Point& three)
{
  double area = 0.5 * std::abs(one.x * (two.y - three.y) + two.x * (three.y - one.y) + three.x * (one.y - two.y));
  two = three;
  return area;
}
double ayupov::calculatePolygonArea(const Polygon& polygon)
{
  GetTriangleArea countTR{polygon.points[0], polygon.points[1]};
  std::vector<double> areas;
  std::transform(polygon.points.begin() + 2, polygon.points.end(), std::back_inserter(areas), countTR);
  double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
  return sum;
}
bool ayupov::isOdd(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}
bool ayupov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}
bool ayupov::isRightSize(const Polygon& polygon, size_t size)
{
  return polygon.points.size() == size;
}
