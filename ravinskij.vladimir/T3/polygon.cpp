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

bool rav::operator<(const Point& lhs, const Point& rhs)
{
  return (lhs.x < rhs.x) && (lhs.y < rhs.y);
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
  std::vector< Point > temp(vertexCount);
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, vertexCount, temp.begin());
  if (in && temp.size() == vertexCount)
  {
    polygon.points = temp;
  }
  return in;
}

bool rav::isEmptyPolygon(const Polygon& polygon)
{
  return polygon.points.empty();
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

double rav::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(PartAreaFunctor{ polygon.points.at(1) }, 0.0, _1, polygon.points.at(0));

  std::vector< double > areas(polygon.points.size());
  std::transform(polygon.points.cbegin(), polygon.points.cend(), areas.begin(), accumulateArea);

  return std::accumulate(areas.cbegin(), areas.cend(), 0.0) / 2;
}

size_t rav::polygonSize(const Polygon& polygon)
{
  return polygon.points.size();
}

bool comparePointsX(const rav::Point& lhs, const rav::Point& rhs)
{
  return lhs.x < rhs.x;
}

bool comparePointsY(const rav::Point& lhs, const rav::Point& rhs)
{
  return lhs.y < rhs.y;
}

int rav::minX(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), comparePointsX)->x;
}

int rav::minY(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), comparePointsY)->y;
}

int rav::maxX(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), comparePointsX)->x;
}

int rav::maxY(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), comparePointsY)->y;
}

bool comparePolygonsMinX(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return minX(lhs) < minX(rhs);
}

bool comparePolygonsMinY(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return minY(lhs) < minY(rhs);
}

bool comparePolygonsMaxX(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return maxX(lhs) < maxX(rhs);
}

bool comparePolygonsMaxY(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  return maxY(lhs) < maxY(rhs);
}


rav::Polygon rav::getFrameRect(const std::vector< Polygon >& polygons)
{
  int pMinX = minX(*std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinX));
  int pMinY = minY(*std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinY));
  int pMaxX = maxX(*std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsMaxX));
  int pMaxY = maxY(*std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsMaxY));

  std::vector< Point > result{ {pMinX, pMinY}, {pMinX, pMaxY}, {pMaxX, pMaxY}, {pMaxX, pMinY} };
  return Polygon{ result };
}

bool rav::operator<=(const Polygon& lhs, const Polygon& rhs)
{
  int thisMinX = minX(lhs);
  int thisMinY = minY(lhs);
  int thisMaxX = maxX(lhs);
  int thisMaxY = maxY(lhs);

  int rhsMinX = minX(rhs);
  int rhsMinY = minY(rhs);
  int rhsMaxX = maxX(rhs);
  int rhsMaxY = maxY(rhs);

  bool res = (thisMinX >= rhsMinX) && (thisMaxX <= rhsMaxX) && (thisMinY >= rhsMinY) && (thisMaxY <= rhsMaxY);
  return res;
}
