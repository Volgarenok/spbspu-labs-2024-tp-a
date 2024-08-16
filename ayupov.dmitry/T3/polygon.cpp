#include "polygon.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <Delimiter.hpp>

std::istream& ayupov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using DelC = DelimiterChar;
  Point temp{0, 0};
  in >> DelC{'('} >> temp.x >> DelC{';'} >> temp.y >> DelC{')'};
  if (in)
  {
    point = temp;
  }
  return in;
}
std::ostream& ayupov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}
std::istream& ayupov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointsNum = 0;
  in >> pointsNum;
  if (pointsNum < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon temp;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{in}, pointsNum - 1, std::back_inserter(temp.points));
  if (in.peek() != '\n')
  {
    std::copy_n(input_it_t{ in }, 1, std::back_inserter(temp.points));
  }
  if (in && (temp.points.size() == pointsNum) && (in.peek() == '\n'))
  {
    polygon = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream& ayupov::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using output_iterator_t = std::ostream_iterator< Point >;
  out << polygon.points.size() << " ";
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_iterator_t{out, " "});
  return out;
}
bool ayupov::operator==(const Point& first, const Point& second)
{
  return ((first.x == second.x) && (first.y == second.y));
}
bool ayupov::operator==(const Polygon& first, const Polygon& second)
{
  if (first.points.size() == second.points.size())
  {
    return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
  }
  return false;
}
