#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include "delimiter.hpp"

std::istream & erohin::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  using del = Delimiter;
  input >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
  return input;
}

std::istream & erohin::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t size = 0;
  input >> size;
  polygon.points.reserve(size);
  std::copy(
    std::istream_iterator< Point >(input),
    std::istream_iterator< Point >(),
    std::back_inserter(polygon.points)
  );
  return input;
}
