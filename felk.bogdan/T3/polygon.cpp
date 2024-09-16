#include "polygon.hpp"

#include <iterator>
#include <algorithm>

#include "delimeter.hpp"

std::istream& felk::operator>>(std::istream& in, Point& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  int x = 0;
  int y = 0;

  in >> del{ '(' } >> x >> del{ ';' } >> y >> del{ ')' };

  if (in)
  {
    data = Point{ x, y };
  }
  return in;
}

bool felk::operator==(const Point& point1, const Point& point2)
{
  return (point1.x == point2.x) && (point1.y == point2.y);
}

std::istream& felk::operator>>(std::istream& in, Polygon& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t n = 0;

  in >> n;

  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  points.reserve(n);
  std::copy_n(std::istream_iterator< Point >{ in }, n, std::back_inserter(points));
  if (in && points.size() == n)
  {
    data = Polygon{ points };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool felk::operator==(const Polygon& poly1, const Polygon& poly2)
{
  return std::equal(poly1.points.cbegin(), poly1.points.cend(), poly2.points.cbegin());
}
