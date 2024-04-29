#include "polygon.hpp"

#include <iostream>
#include <iterator>

#include <delimiter.hpp>

std::istream &zagrivnyy::operator>>(std::istream &in, Point &src)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = zagrivnyy::DelimiterI;
  int x = 0;
  int y = 0;
  in >> del{"("} >> x >> del{";"} >> y >> del{")"};

  if (in)
  {
    src.x = x;
    src.y = y;
  }

  return in;
}

std::istream &zagrivnyy::operator>>(std::istream &in, Polygon &src)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int count = 0;
  in >> count;

  using input_it_t = std::istream_iterator< Point >;
  std::vector< Point > points{count};
  std::copy_n(input_it_t{in}, count, points.begin());

  if (in)
  {
    src.points = std::move(points);
  }

  return in;
}
