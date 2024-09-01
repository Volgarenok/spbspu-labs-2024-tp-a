#include "Polygon.h"
#include <algorithm>
#include <string>
#include <iterator>
#include <functional>
#include <numeric>
#include <iomanip>
#include <Delimiter.h>



namespace kartamyshev
{
  struct Triangle
  {
    kartamyshev::Point first;
    double operator()(double area, const Point& second, const Point& third);
  };
}

double kartamyshev::Triangle::operator()(double res, const Point& second, const Point& third)
{
  res += 0.5 * std::abs((second.x - first.x) * (third.y - first.y) - (second.y - first.y) * (third.x - first.x));
  first = second;
  return res;
}

double kartamyshev::Rectangle::operator*(const Rectangle& p1)
{
  return vertexes.x * p1.vertexes.x + vertexes.y * p1.vertexes.y;
}

double kartamyshev::Rectangle::getLength() const
{
  return std::hypot(vertexes.x, vertexes.y);
}

double kartamyshev::Rectangle::cos(const Rectangle& p1)
{
  return (*this * p1) / (getLength() * p1.getLength());
}

double kartamyshev::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  Triangle support = { polygon.points[1] };
  auto areas = std::bind(support, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0, areas);
}

std::istream& kartamyshev::operator>>(std::istream& in, Point& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point dot{ 0, 0 };
  using del = kartamyshev::DelimiterSym;
  in >> del{ '(' } >> dot.x >> del{ ';' } >> dot.y >> del{ ')' };
  if (in)
  {
    value = dot;
  }
  return in;
}

bool kartamyshev::operator==(const Point& dot1, const Point& dot2)
{
  return ((dot1.x == dot2.x) && (dot1.y == dot2.y));
}

bool kartamyshev::operator<(const Point& dot1, const Point& dot2)
{
  return ((dot1.x < dot2.x) && (dot1.y < dot2.y));
}

bool kartamyshev::operator<=(const Point& dot1, const Point& dot2)
{
  return ((dot1 < dot2) || (dot1 == dot2));
}


std::istream& kartamyshev::operator>>(std::istream& in, Polygon& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countDot = 0;
  in >> countDot;
  if (countDot < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > polygon;
  using inIt = std::istream_iterator< Point >;
  std::copy_n(inIt{ in }, countDot, std::back_inserter(polygon));
  if (in && countDot == polygon.size())
  {
    value.points = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
