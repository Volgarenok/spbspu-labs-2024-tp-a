#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <delimiterI.hpp>

namespace kravchenko
{
  struct AccumulatePolygonArea
  {
    Point p1;
    double operator()(double acc, const Point& p2, const Point& p3);
  };
  struct RightAnglePred
  {
    Point side1;
    Point apex;
    bool operator()(const Point& side2);
  };
}

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

std::istream& kravchenko::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t nVertexes = 0;
  in >> nVertexes;
  if (nVertexes < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp(nVertexes);
  using InputItP = std::istream_iterator< Point >;
  std::copy_n(InputItP{ in }, nVertexes, temp.begin());

  if (in)
  {
    p.points = temp;
  }

  return in;
}

size_t kravchenko::getNumberOfVertexes(const Polygon &p)
{
  return p.points.size();
}

double kravchenko::getArea(const Polygon &p)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(AccumulatePolygonArea{ p.points[1] }, _1, _2, p.points[0]);
  return std::accumulate(p.points.cbegin(), p.points.cend(), 0.0, areaAcc);
}

double kravchenko::AccumulatePolygonArea::operator()(double acc, const Point& p2, const Point& p3)
{
  acc += 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return acc;
}

bool kravchenko::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool kravchenko::isIdentical(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return (std::mismatch(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin()).first == p1.points.cend());
}

bool kravchenko::hasRightAngle(const Polygon& p)
{
  auto findPred = RightAnglePred{ p.points[p.points.size() - 2], p.points[p.points.size() - 1] };
  return (std::find_if(p.points.cbegin(), p.points.cend(), findPred) != p.points.cend());
}

bool kravchenko::RightAnglePred::operator()(const Point& side2)
{
  Point vec1{ apex.x - side1.x, apex.y - side1.y };
  Point vec2{ apex.x - side2.x, apex.y - side2.y };
  side1 = apex;
  apex = side2;
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}
