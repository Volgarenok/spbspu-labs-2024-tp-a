#include "polygon.hpp"
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "delimiter.hpp"
#include "commandsSolving.hpp"

struct AccumulateArea
{
  novokhatskiy::Point p1;
  double operator()(double& res, const novokhatskiy::Point& p2, const novokhatskiy::Point& p3)
  {
    res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
    p1 = p2;
    return res;
  }
};

bool novokhatskiy::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y)) || ((lhs.x == rhs.y) && (lhs.y == rhs.x));
}

std::istream& novokhatskiy::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp = {};
  in >> strictDel{ '(' } >> tmp.x >> strictDel{ ';' } >> tmp.y >> strictDel{ ')' };
  if (in)
  {
    p = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& novokhatskiy::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t countPoints = {};
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  using InputIt = std::istream_iterator< Point >;
  std::copy_n(InputIt{ in }, countPoints, std::back_inserter(tmp));
  if (in)
  {
    p.points = tmp;
  }
  return in;
}

bool novokhatskiy::operator<(const Point& lhs, const Point& rhs)
{
  if (lhs.x == rhs.x)
  {
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}

bool novokhatskiy::operator<(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

double novokhatskiy::getArea(const Polygon& points)
{
  using namespace std::placeholders;
  auto res = std::bind(AccumulateArea{points.points[1]}, _1, _2, points.points[0]);
  return std::accumulate(points.points.cbegin(), points.points.cend(), 0.0, res);
}
