#include "DataStruct.h"
#include <iterator>
#include <algorithm>
#include <HelperStructsIO.h>

std::istream& stepanov::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using sep = DelimeterIO;
  in >> sep{'('};
  in >> dest.x_;
  in >> sep{';'};
  in >> dest.y_;
  in >> sep{')'};
  return in;
}

std::istream& stepanov::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  using iter = std::istream_iterator< Point >;
  dest.points_.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points_));
  if (dest.points_.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

 
