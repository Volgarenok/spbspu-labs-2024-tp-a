#include "polygon.hpp"
#include <delimeters.hpp>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

bool namestnikov::operator==(const Point & first, const Point & second)
{
  return ((first.x == second.x) && (first.y == second.y));
}

bool namestnikov::operator<(const Point & first, const Point & second)
{
  return ((first.x < second.x) && (first.y < second.y));
}

bool namestnikov::operator<=(const Point & first, const Point & second)
{
  return ((first.x <= second.x) && (first.y <= second.y));
}

bool namestnikov::operator>=(const Point & first, const Point & second)
{
  return ((first.x >= second.x) && (first.y >= second.y));
}


std::istream & namestnikov::operator>>(std::istream & in, Point & point)
{
  using delC = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point tempPoint = {0, 0};
  in >> delC{'('} >> tempPoint.x >> delC{';'} >> tempPoint.y >> delC{')'};
  if (in)
  {
    point = tempPoint;
  }
  return in;
}

bool namestnikov::operator==(const Polygon & first, const Polygon & second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
}

double namestnikov::getPolygonArea(const Polygon & polygon)
{
  using namespace std::placeholders;
  auto areaFunc = std::bind(PolygonArea{polygon.points[1]}, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, areaFunc);
}

double namestnikov::PolygonArea::operator()(double area, const Point & second, const Point & third)
{
  area += 0.5 * std::abs((third.y - first.y) * (second.x - first.x) - (third.x - first.x) * (second.y - first.y));
  first = second;
  return area;
}

std::istream & namestnikov::operator>>(std::istream & in, Polygon & polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointsCount = 0;
  in >> pointsCount;
  if (pointsCount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tempPolygon;
  using input_iterator_t = std::istream_iterator< Point >;
  std::copy_n(input_iterator_t{in}, pointsCount, std::back_inserter(tempPolygon));
  if (in && (tempPolygon.size() == pointsCount))
  {
    polygon.points = tempPolygon;
  }
  return in;
}
