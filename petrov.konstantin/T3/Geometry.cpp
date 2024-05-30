#include "Geometry.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <numeric>
#include <functional>
#include <stdexcept>
#include "Delimiter.hpp"
#include "Utils.hpp"

std::istream& petrov::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  Point input{ 0,0 };
  using del = petrov::DelimiterI;
  in >> del{ '(' } >> input.x >> del{ ';' } >> input.y >> del{ ')' };
  if (in)
  {
    dest = input;
  }

  return in;
}
std::ostream& petrov::operator<<(std::ostream& out, const Point& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << '(' << src.x << ';' << src.y << ')';
  return out;
}
bool petrov::operator==(const Point& p1, const Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}
petrov::Point petrov::getDelta(const Point& p1, const Point& p2)
{
  return { p2.x - p1.x, p2.y - p1.y };
}

std::istream& petrov::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  dest.points.clear();
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  std::istream_iterator< Point > inIt(in);
  std::copy_n(inIt, size, std::back_inserter(tmp));
  if (in && size == tmp.size())
  {
    dest = { tmp };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream& petrov::operator<<(std::ostream& out, const Polygon& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  std::ostream_iterator< Point > outIt(out, " ");
  std::copy(src.points.begin(), src.points.end(), outIt);
  return out;
}
bool petrov::operator==(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::equal(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin());
}

double petrov::getArea(const Polygon& src)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(AccPolygonAreaPart{ src.points[1] }, _1, _2, src.points[0]);
  return 0.5 * std::accumulate(src.points.cbegin(), src.points.cend(), 0.0, areaAcc);
}
