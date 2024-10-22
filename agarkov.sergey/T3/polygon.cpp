#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <iotypes.hpp>

std::istream& agarkov::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('};
  in >> dest.x_;
  in >> DelimiterIO{';'};
  in >> dest.y_;
  in >> DelimiterIO{')'};
  return in;
}
 
