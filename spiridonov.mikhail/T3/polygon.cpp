#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include "delimeter.hpp"

std::istream& spiridonov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = spiridonov::DelimeterChar;
  Point temp{ 0, 0 };
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

std::istream& spiridonov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  size_t realPointsNumber = 0;
  bool unexpectedPoint = false;
  std::generate_n(std::back_inserter(points), n,
    [&]() {
      Point point{ 0, 0 };
      if (in.peek() == '\n' && realPointsNumber != n)
      {
        unexpectedPoint = true;
      }
      else if (in >> point)
      {
        realPointsNumber++;
        return point;
      }
      return Point{};
    });

  if (in.peek() != '\n' || unexpectedPoint)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    polygon.points = points;
  }
  return in;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using output = std::ostream_iterator< Point >;
  out << polygon.points.size() << ' ';
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output{ out, " " });
  return out;
}

double spiridonov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(AccumulatePolygonArea{ points[1] }, _1, _2, points[0]);
  return std::accumulate(points.cbegin(), points.cend(), 0.0, areaAcc);
}

double spiridonov::AccumulatePolygonArea::operator()(double acc, const Point& point2, const Point& point3)
{
  acc += 0.5 * std::abs((point2.x - point1.x) * (point3.y - point1.y) - (point3.x - point1.x) * (point2.y - point1.y));
  point1 = point2;
  return acc;
}

bool spiridonov::Point::operator==(const Point& point) const
{
  return (x == point.x) && (y == point.y);
}

bool spiridonov::Polygon::isIdentical(const Polygon& polygon) const
{
  if (points.size() != polygon.points.size())
  {
    return false;
  }
  return (std::mismatch(points.cbegin(), points.cend(), polygon.points.cbegin()).first == points.cend());
}

bool spiridonov::Polygon::isLessArea(const Polygon& polygon) const
{
  return (getArea() > polygon.getArea());
}
