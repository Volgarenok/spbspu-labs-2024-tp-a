#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <delimiter.hpp>

std::istream& skuratov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point pos = {};

  in >> del{ '(' } >> pos.x >> del{ ';' } >> pos.y >> del{ ')' };
  if (in)
  {
    point = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& skuratov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

std::istream& skuratov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t verticesNumb = {};
  in >> verticesNumb;

  std::vector< Point > pos;
  using inputItT = std::istream_iterator< Point >;
  std::copy_n(inputItT{ in }, verticesNumb, std::back_inserter(pos));

  if (pos.size() == verticesNumb)
  {
    polygon.points = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& skuratov::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  using outputItT = std::ostream_iterator< Point >;
  out << polygon.points.size() << ' ';
  std::copy(polygon.points.cbegin(), polygon.points.cend(), outputItT{ out, " " });
  return out;
}

double skuratov::calculateArea::operator()(double res, const Point& point2, const Point& point3)
{
  res += 0.5 * (std::abs((point2.x - point1.x) * (point3.y - point1.y) - (point3.x - point1.x) * (point2.y - point1.y)));
  point1 = point2;
  return res;
}

double skuratov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto res = std::bind(calculateArea{ points[1] }, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, res);
}
