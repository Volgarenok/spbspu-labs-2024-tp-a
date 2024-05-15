#include "datastruct.hpp"
#include "delimeter.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <math.h>

bool kuznetsov::Point::operator<=(const Point& point)
{
  return (this->x <= point.x && this->y <= point.y);
}

bool kuznetsov::Point::operator>=(const Point& point)
{
  return (this->x >= point.x && this->y >= point.y);
}

std::istream& kuznetsov::operator>>(std::istream& in, Point& point)
{
  using delchr = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> delchr{ '(' } >> x >> delchr{ ';' } >> y >> delchr{ ')' };
  if (in)
  {
    point = { x, y };
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, Polygon& polygon)
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
  std::vector< Point > points;
  using input_it_t = std::istream_iterator< kuznetsov::Point >;
  std::copy_n(input_it_t{ in }, n, std::back_inserter(points));
  if (in && n == points.size())
  {
    polygon = { points };
  }
  return in;
}

double kuznetsov::getLength(const Point& a, const Point& b)
{
  return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

double kuznetsov::Triangle::getArea()
{
  double ab = getLength(a, b);
  double bc = getLength(b, c);
  double ac = getLength(a, c);
  double p = (ab + bc + ac) / 2;
  return std::sqrt(p * (p - ab) * (p - bc) * (p - ac));
}

double kuznetsov::getAreaWithNextPoint(double sum, Triangle& triangle, const Point& newPoint)
{
  triangle.b = triangle.c;
  triangle.c = newPoint;
  return sum += triangle.getArea();
}

double kuznetsov::getAreaPolygon(const Polygon& polygon)
{
  using namespace std::placeholders;
  Triangle triangle{ polygon.points[0], polygon.points[1], polygon.points[2] };
  double area = triangle.getArea();
  if (polygon.points.size() > 3)
  {
    auto operation = std::bind(getAreaWithNextPoint, _1, triangle, _2);
    area += std::accumulate(polygon.points.begin() + 2, polygon.points.end(), 0.0, operation);
  }
  return area;
}

double kuznetsov::getAreaEvenOrOdd(bool cur, double sum, const Polygon& polygon)
{
  if (cur == false && polygon.points.size() % 2 == 1)
  {
    return sum += getAreaPolygon(polygon);
  }
  else if (cur == true && polygon.points.size() % 2 == 0)
  {
    return sum += getAreaPolygon(polygon);
  }
  else
  {
    return sum;
  }
}

double kuznetsov::getAreaPolygonForMean(double sum, const Polygon& polygon)
{
  return sum += getAreaPolygon(polygon);
}

double kuznetsov::getAreaPolygonForNum(size_t num, double sum, const Polygon& polygon)
{
  if (polygon.points.size() == num)
  {
    return sum += getAreaPolygon(polygon);
  }
  return sum;
}
