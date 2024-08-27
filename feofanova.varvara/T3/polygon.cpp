#include "polygon.hpp"
#include "delimeter.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

std::istream& feofanova::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tempPoint = {};
  using del = delimeter_t;
  in >> del{ '(' } >> tempPoint.x >> del{ ';' } >> tempPoint.y >> del{ ')' };
  if (in)
  {
    p = tempPoint;
  }
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& feofanova::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t countPoints = 0;
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  poly.points.clear();
  std::copy_n(
      std::istream_iterator< Point >(in),
      countPoints,
      std::back_inserter(poly.points)
  );
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << p.points.size() << ' ';
  using outIt = std::ostream_iterator<Point>;
  std::copy(p.points.cbegin(), p.points.cend(), outIt{ out, " " });
  return out;
}
