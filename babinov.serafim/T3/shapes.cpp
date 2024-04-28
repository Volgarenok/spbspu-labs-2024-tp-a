#include "shapes.hpp"
#include <algorithm>
#include <cmath>
#include <delimiters.hpp>
#include <ios>
#include <iostream>
#include <iterator>
#include <utility>

bool babinov::Point::operator<(const Point& other) const
{
  return (x < other.x) && (y < other.y);
}

bool babinov::Point::operator>=(const Point& other) const
{
  return !(*this < other);
}

bool babinov::Point::operator<=(const Point& other) const
{
  return !(other < *this);
}

babinov::Vector::Vector(const Point& begin, const Point& end):
  coords(babinov::Point{end.x - begin.x, end.y - begin.y})
{}

double babinov::Vector::operator*(const Vector& other) const
{
  return (coords.x * other.coords.x) + (coords.y * other.coords.y);
}

double babinov::Vector::getLength() const
{
  return std::sqrt(std::pow(coords.x, 2) + std::pow(coords.y, 2));
}

double babinov::Vector::findCosBetween(const Vector& other) const
{
  return (*this * other) / (getLength() * other.getLength());
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
