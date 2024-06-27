#include "polygon.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "delimiter.hpp"

std::istream& ayupov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using DelC = DelimiterChar;
  Point temp;
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
  int pointsNum = 0;
  in >> pointsNum;
  if (pointsNum < 3)
  {
    in.setstate(std::ios::failbit);
  }
  Polygon temp;
  using input_it_t = std::istream_iterator<Point>;
  std::copy_n(input_it_t{in}, pointsNum, std::back_inserter(temp.points));
  if (in)
  {
    polygon = temp;
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
