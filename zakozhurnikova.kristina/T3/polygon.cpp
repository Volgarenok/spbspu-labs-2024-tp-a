#include <algorithm>
#include <delimiter.hpp>
#include <functional>
#include <iterator>
#include <numeric>
#include <scopeGuard.hpp>
#include "commandImpl.hpp"
#include "polygon.hpp"

std::istream& zakozhurnikova::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = zakozhurnikova::DelimiterChar;
  Point tmp{ 0, 0 };
  in >> del{ '(' } >> tmp.x >> del{ ';' } >> tmp.y >> del{ ')' };
  if (in)
  {
    point = tmp;
  }
  return in;
}

bool zakozhurnikova::Point::operator==(const Point& rhs) const
{
  return (x == rhs.x) && (y == rhs.y);
}

bool zakozhurnikova::Point::operator<(const Point& rhs) const
{
  return (x < rhs.x) && (y < rhs.y);
}

bool zakozhurnikova::Point::operator<=(const Point& rhs) const
{
  return (*this < rhs) || (*this == rhs);
}

std::istream& zakozhurnikova::operator>>(std::istream& in, Polygon& polygon)
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
  if (in && temp.size() == vertexCount)
  {
    polygon.points = temp;
  }
  return in;
}

double zakozhurnikova::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(PolygonAreaComputer{ points.at(1) }, _1, _2, points.at(0));
  return std::accumulate(points.cbegin(), points.cend(), 0.0, accumulateArea) / 2;
}

bool zakozhurnikova::equalPolygons(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}
