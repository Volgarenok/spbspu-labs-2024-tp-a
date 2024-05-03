#include "datastruct.hpp"
#include "delimeter.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <math.h>

std::istream& kuznetsov::operator>>(std::istream& in, Point& point)
{
  using delchr = DelimeterChar;
  std::istream::sentry guard(in);
  if (guard)
  {
    int x = 0;
    int y = 0;
    in >> delchr{ '(' } >> x >> delchr{ ';' } >> y >> delchr{ ')' };
    if (in)
    {
      point = { x, y };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    size_t n = 0;
    in >> n;
    std::vector< Point > points;
    using input_it_t = std::istream_iterator< kuznetsov::Point >;
    std::copy_n(input_it_t{ in }, n, std::back_inserter(points));
    if (in)
    {
      polygon = { points };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
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

double kuznetsov::getAreaWithNextPoint(Triangle& triangle, const Point& newPoint)
{
  triangle.b = triangle.c;
  triangle.c = newPoint;
  return triangle.getArea();
}

double kuznetsov::getAreaPolygon(const Polygon& polygon)
{
  using namespace std::placeholders;
  Triangle triangle{ polygon.points[0], polygon.points[1], polygon.points[2] };
  double area = triangle.getArea();
  if (polygon.points.size() > 3)
  {
    auto operation = std::bind(getAreaWithNextPoint, triangle, _2);
    area += std::accumulate(polygon.points.begin() + 3, polygon.points.end(), 0.0, operation);
  }
  return area;
}

double kuznetsov::getAreaEvenOrOdd(bool cur, double sum, const Polygon& polygon);
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

