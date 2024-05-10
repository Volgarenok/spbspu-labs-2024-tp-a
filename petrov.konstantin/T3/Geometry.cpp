#include "Geometry.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <numeric>
#include <functional>
#include "Delimiter.h"
#include "Utils.hpp"

std::istream& petrov::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  Point input;
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
  std::istream_iterator< Point > inIt(in);
  std::copy_n(inIt, size, std::back_inserter(dest.points));

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

double petrov::getArea(const Polygon& src)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(AccPolygonAreaPart{ src.points[1] }, _1, _2, src.points[0]);
  return 0.5 * std::accumulate(src.points.cbegin(), src.points.cend(), 0.0, areaAcc);
}
