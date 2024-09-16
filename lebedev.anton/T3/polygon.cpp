#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

struct AccumulateTriangleArea
{
  lebedev::Point p2;
  double operator()(const lebedev::Point & p1, const lebedev::Point & p3)
  {
    double area = 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
    p2 = p3;
    return area;
  }
};

std::istream & lebedev::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t points_num = 0;
  input >> points_num;
  if (points_num < 3)
  {
    input.setstate(std::ios::failbit);
  }
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >(input), points_num, std::back_inserter(points));
  if (input)
  {
    polygon.points = std::move(points);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

double lebedev::getArea(const Polygon & polygon)
{
  std::vector< double > areas;
  areas.reserve(polygon.points.size() - 2);
  const Point & point_top = polygon.points[0];
  using namespace std::placeholders;
  auto area_funct = std::bind(AccumulateTriangleArea{ polygon.points[1] }, point_top, _1);
  std::transform(polygon.points.cbegin() + 2, polygon.points.cend(), std::back_inserter(areas), area_funct);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}
