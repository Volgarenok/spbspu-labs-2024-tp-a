#include "shape.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <delimiter.hpp>

zaitsev::Point zaitsev::operator+(Point pt1, Point pt2)
{
  return { pt1.x + pt2.x, pt1.y + pt2.y };
}

zaitsev::Point zaitsev::operator-(Point pt1, Point pt2)
{
  return { pt1.x - pt2.x, pt1.y - pt2.y };
}

std::istream& zaitsev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimiter;

  int x = 0;
  int y = 0;

  in >> del{ "(" } >> x >> del{ ";" } >> y >> del{ ")" };

  if (in)
  {
    point = Point{ x , y };
  }
  return in;
}

std::istream& zaitsev::operator>>(std::istream& in, Polygon& poly)
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

  std::vector <Point> points;
  points.reserve(n);
  using input_it_t = std::istream_iterator<Point>;
  std::copy_n(input_it_t{ in }, n, std::back_inserter(points));

  if (in)
  {
    poly.points = points;
  }
  return in;
}
