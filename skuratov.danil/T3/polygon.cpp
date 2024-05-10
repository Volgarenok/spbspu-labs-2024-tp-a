#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <delimiter.hpp>

std::istream& skuratov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point pos = { 0, 0 };

  in >> del{ '(' } >> pos.x >> del{ ';' } >> pos.y >> del{ ')' };
  if (in)
  {
    point = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& skuratov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t verticesNumb = {};
  in >> verticesNumb;

  std::vector< Point > pos;
  using inputItT = std::istream_iterator< Point >;
  std::copy_n(inputItT{ in }, verticesNumb, std::back_inserter(pos));

  if (pos.size() == verticesNumb)
  {
    polygon.points = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
