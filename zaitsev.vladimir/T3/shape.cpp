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

std::istream& zaitsev::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t vertexes{};
  in >> vertexes;
  if (vertexes < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector < Point > points{};
  std::copy_n(std::istream_iterator < Point >(in),
    vertexes,
    std::back_inserter(points));
  if (in && vertexes == points.size())
  {
    polygon.points = points;
  }
  else
  {
    in.clear();
    in.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& zaitsev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  in >> Delimiter{ "(" } >> point.x >> Delimiter{ ";" } >> point.y >> Delimiter{ ")" };
  return in;
}
