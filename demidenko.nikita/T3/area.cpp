#include "area.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
#include "geometry.hpp"

double demidenko::polygonArea(const Polygon& polygon)
{
  std::vector< std::pair< Point, Point > > lines;
  // Баг в шланг формате.
  // clang-format off
  std::transform(
    polygon.points.begin() + 2,
    polygon.points.end(),
    polygon.points.begin() + 1,
    std::back_inserter(lines),
    std::make_pair< Point, Point >
  );
  // clang-format on
  std::vector< Triangle > triangles;
  std::transform(
    lines.begin(),
    lines.end(),
    polygon.points.begin(),
    std::back_inserter(triangles),
    buildTriangle
  );
  using namespace std::placeholders;
  return std::accumulate(
    triangles.begin(),
    triangles.end(),
    0.0,
    std::bind(std::plus<>{}, _1, std::bind(&Triangle::area, _2))
  );
}
demidenko::Triangle demidenko::buildTriangle(
  const std::pair< Point, Point >& base, const Point& top
)
{
  return Triangle{ top, base.first, base.second };
}
double demidenko::Triangle::area() const
{
  double a = distance(first, second);
  double b = distance(second, third);
  double c = distance(third, first);
  double p = (a + b + c) / 2;
  return std::sqrt(p * (p - a) * (p - b) * (p - c));
}
double demidenko::distance(const Point& first, const Point& second)
{
  return std::hypot(first.x - second.x, first.y - second.y);
}
