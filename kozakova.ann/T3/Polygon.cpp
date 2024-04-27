#include "Polygon.hpp"
#include <algorithm>
#include <iterator>
#include "Delimiter.hpp"

std::istream& kozakova::operator>>(std::istream& in, Point& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = kozakova::Delimiter;
  int x = 0;
  int y = 0;
  in >> del{ '(' } >> x >> del{ ';' } >> y >> del{ ')' };
  if (in)
  {
    value = Point{ x,y };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool kozakova::Point::operator<(const Point& p) const
{
  if (x != p.x)
  {
    return x < p.x;
  }
  return y < p.y;
}

bool kozakova::Point::operator==(const Point& p) const
{
  return x == p.x && y == p.y;
}

std::istream& kozakova::operator>>(std::istream& in, Polygon& value)
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
  using inputItT = std::istream_iterator< kozakova::Point >;
  std::vector < Point > vec;
  vec.reserve(n);
  std::copy_n(inputItT{ in }, n, std::back_inserter(vec));
  // неформат самих точек?
  // меньше точек чем надо??
  if (in && vec.size() == n)
  {
    value = Polygon{ vec };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool kozakova::Polygon::operator==(const Polygon& p) const
{
  return points == p.points;
}

double kozakova::PolygonArea::operator()(double area, const Point& second)
{
  area += (second.x + first.x) * (first.y - second.y);
  first = second;
  return area;
}

double kozakova::Polygon::getArea() const
{
  double area = std::accumulate(points.begin(), points.end(), 0.0, PolygonArea{ points[0] });
  area += (points[points.size() - 1].x + points[0].x) * (points[points.size() - 1].y - points[0].y);
  return std::abs(area) / 2;
}

bool kozakova::Polygon::isRect()
{
  std::sort(points.begin(), points.end());
  double x1 = points[0].x - points[1].x;
  double y1 = points[0].y - points[1].y;
  double x2 = points[0].x - points[2].x;
  double y2 = points[0].y - points[2].y;
  double x3 = points[3].x - points[1].x;
  double y3 = points[3].y - points[1].y;
  double x4 = points[3].x - points[2].x;
  double y4 = points[3].y - points[2].y;
  return x1 * x2 + y1 * y2 == 0 && x3 * x1 + y3 * y1 == 0 && x3 * x4 + y3 * y4 == 0;
}
