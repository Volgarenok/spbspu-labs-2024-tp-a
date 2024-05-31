#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include "point.hpp"

std::istream& zaparin::operator>>(std::istream& in, Polygon& plg)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t pointsCount = 0;
  in >> pointsCount;

  if (pointsCount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;

  using in_it = std::istream_iterator< Point >;
  std::copy_n(in_it{ in }, pointsCount, std::back_inserter(temp));

  if (in && temp.size() == pointsCount)
  {
    plg.points = temp;
  }

  return in;
}

