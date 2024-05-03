#include "polygon.hpp"
#include <delimeters.hpp>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

bool namestnikov::Point::operator==(const Point & other) const
{
  return ((x == other.x) && (y == other.y));
}

bool namestnikov::Point::operator<(const Point & other) const
{
  return ((x < other.x) && (y < other.y));
}

bool namestnikov::Point::operator>(const Point & other) const
{
  return ((x > other.x) && (y > other.y));
}

bool namestnikov::Point::operator<=(const Point & other) const
{
  return !(*this > other);
}

bool namestnikov::Point::operator>=(const Point & other) const
{
  return !(*this < other);
}

std::istream & namestnikov::operator>>(std::istream & in, namestnikov::Point & point)
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

std::ostream & namestnikov::operator<<(std::ostream & out, const namestnikov::Point & point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool namestnikov::operator==(const Polygon & first, const Polygon & second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
}

double namestnikov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto areaFunc = std::bind(PolygonArea{points[1]}, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, areaFunc);
}

double namestnikov::PolygonArea::operator()(double area, const namestnikov::Point & second, const namestnikov::Point & third)
{
  area += 0.5 * std::abs((third.y - first.y) * (second.x - first.x) - (third.x - first.x) * (second.y - first.y));
  first = second;
  return area;
}

std::istream & namestnikov::operator>>(std::istream & in, namestnikov::Polygon & polygon)
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
  }
  else
  {
    std::vector< Point > tempPolygon;
    using input_iterator_t = std::istream_iterator< Point >;
    std::copy_n(input_iterator_t{in}, pointsCount, std::back_inserter(tempPolygon));
    if (in)
    {
      polygon.points = tempPolygon;
    }
  }
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const namestnikov::Polygon & polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  using output_iterator_t = std::ostream_iterator< Point >;
  out << polygon.points.size() << " ";
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_iterator_t{out, " "});
  return out;
}
