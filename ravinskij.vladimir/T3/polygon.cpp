#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <limits>
#include <functional>
#include <numeric>
#include "partAreaFunctor.hpp"

std::istream& ravinskij::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = ravinskij::CharDelimeter;
  Point temp{ 0, 0 };
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

std::ostream& ravinskij::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool ravinskij::Point::operator==(const Point& rhs) const
{
  return (x == rhs.x) && (y == rhs.y);
}

bool ravinskij::Point::operator<(const Point& rhs) const
{
  return (x < rhs.x) && (y < rhs.y);
}

bool ravinskij::Point::operator<=(const Point& rhs) const
{
  return (*this == rhs) || (*this < rhs);
}

bool ravinskij::Point::operator>=(const Point& rhs) const
{
  return !(*this < rhs);
}

std::istream& ravinskij::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::size_t vertexCount = 0;
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
  if(in && temp.size() == vertexCount)
  {
    polygon.points = temp;
  }
  return in;
}

std::ostream& ravinskij::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  using output_it_t = std::ostream_iterator< ravinskij::Point >;
  const auto& points = polygon.points;
  std::copy(points.cbegin(), points.cend(), output_it_t{ out, " "});
  return out;
}

bool ravinskij::Polygon::empty() const
{
  return points.empty();
}

bool ravinskij::Polygon::operator==(const Polygon& rhs) const
{
  if (points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(points.cbegin(), points.cend(), rhs.points.cbegin());
}

double ravinskij::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(PartAreaFunctor{ points.at(1) }, _1, _2, points.at(0));
  return std::accumulate(points.cbegin(), points.cend(), 0.0, accumulateArea) / 2;
}

std::size_t ravinskij::Polygon::size() const
{
  return points.size();
}

bool comparePointsX(const ravinskij::Point& lhs, const ravinskij::Point& rhs)
{
  return lhs.x < rhs.x;
}

bool comparePointsY(const ravinskij::Point& lhs, const ravinskij::Point& rhs)
{
  return lhs.y < rhs.y;
}

int ravinskij::Polygon::minX() const
{
  return std::min_element(points.cbegin(), points.cend(), comparePointsX)->x;
}

int ravinskij::Polygon::minY() const
{
  return std::min_element(points.cbegin(), points.cend(), comparePointsY)->y;
}

int ravinskij::Polygon::maxX() const
{
  return std::max_element(points.cbegin(), points.cend(), comparePointsX)->x;
}

int ravinskij::Polygon::maxY() const
{
  return std::max_element(points.cbegin(), points.cend(), comparePointsY)->y;
}

bool comparePolygonsMinX(const ravinskij::Polygon& lhs, const ravinskij::Polygon& rhs)
{
  return lhs.minX() < rhs.minX();
}

bool comparePolygonsMinY(const ravinskij::Polygon& lhs, const ravinskij::Polygon& rhs)
{
  return lhs.minY() < rhs.minY();
}

bool comparePolygonsMaxX(const ravinskij::Polygon& lhs, const ravinskij::Polygon& rhs)
{
  return lhs.maxX() < rhs.maxX();
}

bool comparePolygonsMaxY(const ravinskij::Polygon& lhs, const ravinskij::Polygon& rhs)
{
  return lhs.maxY() < rhs.maxY();
}



ravinskij::Polygon ravinskij::getFrameRect(const std::vector< Polygon >& polygons)
{
  int minX = std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinX)->minX();
  int minY = std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinY)->minY();
  int maxX = std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinX)->maxX();
  int maxY = std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsMinX)->maxY();

  std::vector< Point > result{ {minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY} };
  return Polygon{ result };
}

bool ravinskij::Polygon::operator<(const Polygon& rhs) const
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
