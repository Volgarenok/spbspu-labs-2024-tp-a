#include "polygon.hpp"
#include <algorithm>
#include <iterator>

std::istream& novikov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t n;
  in >> n;
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >{ in }, n, std::back_inserter(points));
  if (in)
  {
    polygon.points = std::move(points);
  }
  return in;
}
