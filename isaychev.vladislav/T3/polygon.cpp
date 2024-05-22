#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>

std::istream & isaychev::operator>>(std::istream & in, Polygon & p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t pntNum = 0;
  in >> pntNum;

  using iterI_t = std::istream_iterator< Point >;

  std::copy_n(iterI_t{in}, pntNum, std::back_inserter(p.points));

  return in;
}
