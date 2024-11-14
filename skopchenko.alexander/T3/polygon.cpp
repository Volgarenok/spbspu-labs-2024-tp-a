#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include "delimeters.hpp"

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

std::istream& skopchenko::operator>>(std::istream& in, Point& point)
{
  using delC = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point tempPoint = { 0, 0 };
  in >> delC{ '(' } >> tempPoint.x >> delC{ ';' } >> tempPoint.y >> delC{ ')' };
  if (in)
  {
    point = tempPoint;
  }
  return in;
}

bool skopchenko::operator==(const Polygon& first, const Polygon& second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
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

std::istream& skopchenko::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointsCount = 0;
  in >> pointsCount;
  if (pointsCount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tempPolygon;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, (pointsCount - 1), std::back_inserter(tempPolygon));
  if (in.peek() != '\n')
  {
    std::copy_n(input_it_t{ in }, 1, std::back_inserter(tempPolygon));
  }
  if (in && (tempPolygon.size() == pointsCount) && ((in.peek() == '\n')))
  {
    polygon.points = tempPolygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
