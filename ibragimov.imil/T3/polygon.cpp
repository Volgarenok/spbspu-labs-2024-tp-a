#include "polygon.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

std::istream& ibragimov::operator>>(std::istream& in, Polygon& rhs)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int n = 0;
  in >> n;
  if (in)
  {
    rhs.points.resize(n);
    std::copy_n(std::istream_iterator< Point >{in}, n, rhs.points.begin());

    // if (n < rhs.points.size())
    // {
    //   in.setstate(std::ios::failbit);
    // }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

size_t ibragimov::getSize(const Polygon &value)
{
  return value.points.size();
}

double ibragimov::getArea(const Polygon &value)
{
  return 1;
}
