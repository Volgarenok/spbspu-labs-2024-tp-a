#include "polygon.hpp"
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <delimiter.hpp>
#include <scopeGuard.hpp>
#include "commandImpl.hpp"

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
