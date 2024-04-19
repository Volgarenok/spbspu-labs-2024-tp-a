#include "polygon.hpp"

#include <algorithm>
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
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    std::copy_n(std::istream_iterator< Point >{in}, n, std::back_inserter(rhs.points));
  }
  return in;
}
