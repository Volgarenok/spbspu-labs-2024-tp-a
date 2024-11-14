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

bool agarkov::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
}

std::istream& agarkov::operator>>(std::istream& in, Polygon& dest)
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

bool agarkov::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points_ == rhs.points_;
}
