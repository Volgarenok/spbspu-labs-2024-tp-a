#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <delimiter.hpp>
#include <scopeGuard.hpp>

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
  return 0;
}
