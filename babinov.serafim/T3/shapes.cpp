#include "shapes.hpp"
#include <algorithm>
#include <delimiters.hpp>
#include <ios>
#include <iostream>
#include <iterator>
#include <utility>

babinov::Point& babinov::Point::operator=(const Point& other)
{
  if (this != &other)
  {
    x = other.x;
    y = other.y;
  }
  return *this;
}

std::istream& babinov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = CharDelimiterI;
  int x = 0;
  int y = 0;
  in >> del::insensitive('(') >> x >> del::insensitive(';');
  in >> y >> del::insensitive(')');
  if (in)
  {
    point.x = x;
    point.y = y;
  }
  return in;
}

std::istream& babinov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using input_it_t = std::istream_iterator< Point >;
  using del = CharDelimiterI;
  int nVertexes = 0;
  in >> nVertexes;
  std::vector< Point > points(nVertexes);
  std::copy_n(input_it_t(in), nVertexes, points.begin());
  if (in)
  {
    polygon.points = std::move(points);
  }
  return in;
}
