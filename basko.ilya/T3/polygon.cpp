#include "polygon.hpp"
#include <delimiters.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

std::istream& basko::operator>>(std::istream& in, Point& point)
{
  using delChar = DelimiterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp = { 0, 0 };
  in >> delChar{ '(' } >> temp.x >> delChar{ ';' } >> temp.y >> delChar{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

bool basko::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool basko::operator<=(const Polygon& lhs, const Polygon& rhs)
{
  int innerMinX = findMinX(lhs);
  int innerMinY = findMinY(lhs);
  int innerMaxX = findMaxX(lhs);
  int innerMaxY = findMaxY(lhs);
  int outerMinX = findMinX(rhs);
  int outerMinY = findMinY(rhs);
  int outerMaxX = findMaxX(rhs);
  int outerMaxY = findMaxY(rhs);
  return (innerMinX >= outerMinX) && (innerMaxX <= outerMaxX) && (innerMinY >= outerMinY) && (innerMaxY <= outerMaxY);
}

double basko::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AreaPolygon{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}

std::istream& basko::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countPoints = 0;
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  using input_iterator_t = std::istream_iterator< Point >;
  std::copy_n(input_iterator_t{ in }, countPoints, std::back_inserter(temp));
  if (in)
  {
    polygon.points = std::move(temp);
  }
  return in;
}

bool basko::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}

double basko::AreaPolygon::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.x) - (p3.x - p1.x) * (p2.y - p1.y)) / 2;
  p1 = p2;
  return area;
}

bool basko::isRightAngle(const Polygon& polygon)
{
  auto countAngle = accumulateRightAngle{ polygon.points[polygon.points.size() - 2],polygon.points[polygon.points.size() - 1] };
  return (std::find_if(polygon.points.cbegin(), polygon.points.cend(), countAngle) != polygon.points.cend());
}

bool compareByX(const basko::Point& lhs, const basko::Point& rhs)
{
  return lhs.x < rhs.x;
}

bool compareByY(const basko::Point& lhs, const basko::Point& rhs)
{
  return lhs.y < rhs.y;
}

int basko::findMaxX(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}

int basko::findMaxY(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}

int basko::findMinX(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}

int basko::findMinY(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}

bool comparePolygonsByMaxX(const basko::Polygon& lhs, const basko::Polygon& rhs)
{
  return findMaxX(lhs) < findMaxX(rhs);
}

bool comparePolygonsByMaxY(const basko::Polygon& lhs, const basko::Polygon& rhs)
{
  return findMaxY(lhs) < findMaxY(rhs);
}

bool comparePolygonsByMinX(const basko::Polygon& lhs, const basko::Polygon& rhs)
{
  return findMinX(lhs) < findMinX(rhs);
}

bool comparePolygonsByMinY(const basko::Polygon& lhs, const basko::Polygon& rhs)
{
  return findMinY(lhs) < findMinY(rhs);
}

bool basko::accumulateRightAngle::operator()(const Point& p3)
{
  Point vec1{ p2.x - p1.x, p2.y - p1.y };
  Point vec2{ p2.x - p3.x, p2.y - p3.y };
  p1 = p2;
  p2 = p3;
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}
