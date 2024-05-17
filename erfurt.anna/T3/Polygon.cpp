#include "Polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <Delimeter.hpp>
#include "Utilites.hpp"

std::istream & erfurt::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  int x = 0;
  int y = 0;

  in >> del{"("} >> x >> del{";"} >> y >> del{")"};

  if (in)
  {
    point = Point{x , y};
  }
  return in;
}

std::istream & erfurt::operator>>(std::istream & in, Polygon & poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t n = 0;

  in >> n;

  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector <Point> points;
  points.reserve(n);
  using input_it_t = std::istream_iterator<Point>;
  std::copy_n(input_it_t{in}, n, std::back_inserter(points));

  if (in)
  {
    poly.points = points;
  }
  return in;
}

double erfurt::getArea(const Polygon & poly)
{
  using namespace std::placeholders;
  auto area = std::bind(AccumulatePolygonArea{ poly.points[0] }, _1, _2, poly.points[0]);
  return std::accumulate(poly.points.cbegin(), poly.points.cend(), 0.0, area);
}

bool erfurt::isPointConsist(const Point & point, const Polygon & poly)
{
  bool isIn = std::find_if(poly.points.begin(), poly.points.end(),
    [point](const Point& p) {return ((point.x == p.x && point.y == p.y)
      || (point.x == p.y && point.y == p.x)); }) != poly.points.end();
  return isIn;
}

bool erfurt::isEqual(const Polygon & p1, const Polygon & p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::equal(p1.points.begin(), p1.points.end(), p2.points.begin(),
  [](const Point& p1, const Point& p2) {return ((p1.x == p2.x && p1.y == p2.y)); });
}
