#include "figures.hpp"

#include <algorithm>
#include <iterator>

#include <delimiter.hpp>

std::istream &demin::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point temp{0, 0};
  in >> del{"("} >> temp.x >> del{";"} >> temp.y >> del{")"};
  if (in)
  {
    point = temp;
  }
  return in;
}

std::istream &demin::operator>>(std::istream &in, Polygon &poly)
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
  std::vector< Point > temp;
  using inIterator = std::istream_iterator< Point >;
  std::copy_n(inIterator{in}, pointsCount, std::back_inserter(temp));
  if (in && temp.size() == pointsCount)
  {
    poly.points = temp;
  }
  return in;
}
