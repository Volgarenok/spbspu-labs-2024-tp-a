#include "polygon.hpp"
#include <iostream>
#include "../common/delimiter.hpp"

std::istream& strelyaev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = Delimiter;
  return in >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
}