#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <numeric>

bool skopchenko::operator==(const Point& first, const Point& second)
{
  return ((first.x == second.x) && (first.y == second.y));
}

bool skopchenko::operator<(const Point& first, const Point& second)
{
  return ((first.x < second.x) && (first.y < second.y));
}

bool skopchenko::operator<=(const Point& first, const Point& second)
{
  return ((first.x <= second.x) && (first.y <= second.y));
}

bool skopchenko::operator>=(const Point& first, const Point& second)
{
  return ((first.x >= second.x) && (first.y >= second.y));
}

struct PolygonArea
{
  skopchenko::Point first;
  double operator()(double area, const skopchenko::Point& second, const skopchenko::Point& third)
  {
    area += 0.5 * std::abs((third.y - first.y) * (second.x - first.x) - (third.x - first.x) * (second.y - first.y));
    first = second;
    return area;
  }
};

double skopchenko::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto areaFunc = std::bind(PolygonArea{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, areaFunc);
}
