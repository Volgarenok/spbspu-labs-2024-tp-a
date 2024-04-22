#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <delimiterI.hpp>

std::istream& kravchenko::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using cDel = DelimiterI< false >;
  Point temp{ 0, 0 };
  in >> cDel{ '(' } >> temp.x >> cDel{ ';' } >> temp.y >> cDel{ ')' };
  if (in)
  {
    p = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& kravchenko::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t nVertex = 0;
  in >> nVertex;

  std::vector< Point > temp;
  temp.reserve(nVertex);

  // don't know how to replace it w/o cycle
  for (std::size_t i = 0; in && i < nVertex; ++i)
  {
    Point p{ 0, 0 };
    if (in >> p)
    {
      temp.push_back(p);
    }
  }

  if (in)
  {
    p.points = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using outputIt = std::ostream_iterator< Point >;
  out << p.points.size() << ' ';
  std::copy(p.points.cbegin(), p.points.cend(), outputIt{ out, " " });
  return out;
}

double kravchenko::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(AccumulatePolygonArea{ points[1] }, _1, _2, points[0]);
  return std::accumulate(points.cbegin(), points.cend(), 0.0, areaAcc);
}

double kravchenko::AccumulatePolygonArea::operator()(double acc, const Point& p2, const Point& p3)
{
  acc += 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return acc;
}

bool kravchenko::Point::operator==(const Point& other) const
{
  return (x == other.x) && (y == other.y);
}

bool kravchenko::Polygon::isIdentical(const Polygon& other) const
{
  if (points.size() != other.points.size())
  {
    return false;
  }
  return (std::mismatch(points.cbegin(), points.cend(), other.points.cbegin()).first == points.cend());
}

bool kravchenko::Polygon::hasRightAngle() const
{
  auto findPred = RightAnglePred{ points[points.size() - 2], points[points.size() - 1] };
  return (std::find_if(points.cbegin(), points.cend(), findPred) != points.cend());
}

bool kravchenko::RightAnglePred::operator()(const Point& side2)
{
  Point vec1{ apex.x - side1.x, apex.y - side1.y };
  Point vec2{ apex.x - side2.x, apex.y - side2.y };
  side1 = apex;
  apex = side2;
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}
