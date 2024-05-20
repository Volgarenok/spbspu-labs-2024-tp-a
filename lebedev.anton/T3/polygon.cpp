#include "polygon.hpp"
#include <algorithm>
#include <iterator>

std::istream & lebedev::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t points_num = 0;
  input >> points_num;
  if (points_num < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >(input), points_num, std::back_inserter(points));
  if (input)
  {
    polygon.points = std::move(points);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
