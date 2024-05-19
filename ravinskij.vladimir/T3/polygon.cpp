#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <limits>
#include <functional>
#include <numeric>
#include <cmath>
#include <delimeters.hpp>

namespace rav = ravinskij;
std::istream& rav::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = rav::CharDelimeter;
  Point temp{ 0, 0 };
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

bool rav::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool rav::operator<(const Point& lhs, const Point& rhs)
{
  return (lhs.x < rhs.x) && (lhs.y < rhs.y);
}

bool rav::operator<=(const Point& lhs, const Point& rhs)
{
  return (lhs == rhs) || (lhs < rhs);
}

bool rav::operator>=(const Point& lhs, const Point& rhs)
{
  return !(lhs < rhs);
}

std::istream& rav::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexCount = 0;
  in >> vertexCount;
  if (vertexCount < 3)
  {
   in.setstate(std::ios::failbit);
   return in;
  }
  std::vector< Point > temp;
  temp.reserve(vertexCount);
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, vertexCount, std::back_inserter(temp));
  if (in && temp.size() == vertexCount)
  {
    polygon.points = temp;
  }
  return in;
}

bool rav::Polygon::empty() const
{
  return points.empty();
}

bool rav::Polygon::operator==(const Polygon& rhs) const
{
  if (points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(points.cbegin(), points.cend(), rhs.points.cbegin());
}

struct PartAreaFunctor
  {
    rav::Point p1;
    double operator()(double area, const rav::Point& p2, const rav::Point& p3);
  };


double PartAreaFunctor::operator()(double area, const rav::Point& p2, const rav::Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}

double rav::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(PartAreaFunctor{ points.at(1) }, _1, _2, points.at(0));
  return std::accumulate(points.cbegin(), points.cend(), 0.0, accumulateArea) / 2;
}

size_t rav::Polygon::size() const
{
  return points.size();
}

bool comparePointsX(const rav::Point& lhs, const rav::Point& rhs)
{
  return lhs.x < rhs.x;
}

bool comparePointsY(const rav::Point& lhs, const rav::Point& rhs)
{
  return lhs.y < rhs.y;
}

int rav::Polygon::minX() const
{
  return std::min_element(points.cbegin(), points.cend(), comparePointsX)->x;
}

int rav::Polygon::minY() const
{
  return std::min_element(points.cbegin(), points.cend(), comparePointsY)->y;
}

int rav::Polygon::maxX() const
{
  return std::max_element(points.cbegin(), points.cend(), comparePointsX)->x;
}

int rav::Polygon::maxY() const
{
  return std::max_element(points.cbegin(), points.cend(), comparePointsY)->y;
}

bool comparePolygonsMinX(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return lhs.minX() < rhs.minX();
}

bool comparePolygonsMinY(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return lhs.minY() < rhs.minY();
}

bool comparePolygonsMaxX(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return lhs.maxX() < rhs.maxX();
}

bool comparePolygonsMaxY(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return lhs.maxY() < rhs.maxY();
}


rav::Polygon rav::getFrameRect(const std::vector< Polygon >& polygons)
{
  int minX = std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinX)->minX();
  int minY = std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinY)->minY();
  int maxX = std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsMaxX)->maxX();
  int maxY = std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsMaxX)->maxY();

  std::vector< Point > result{ {minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY} };
  return Polygon{ result };
}

bool rav::Polygon::operator<=(const Polygon& rhs) const
{
  int thisMinX = minX();
  int thisMinY = minY();
  int thisMaxX = maxX();
  int thisMaxY = maxY();

  int rhsMinX = rhs.minX();
  int rhsMinY = rhs.minY();
  int rhsMaxX = rhs.maxX();
  int rhsMaxY = rhs.maxY();

  bool res = (thisMinX >= rhsMinX) && (thisMaxX <= rhsMaxX) && (thisMinY >= rhsMinY) && (thisMaxY <= rhsMaxY);
  return res;
}
