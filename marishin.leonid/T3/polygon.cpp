#include "polygon.hpp"
#include <delimeter.hpp>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

bool marishin::Point::operator>=(const Point& data) const
{
  return !(*this < data);
}

bool marishin::Point::operator<=(const Point& data) const
{
  return !(data < *this);
}

bool marishin::Point::operator>(const Point& data) const
{
  return ((x > data.x) && (y > data.y));
}

bool marishin::Point::operator<(const Point& data) const
{
  return ((x < data.x) && (y < data.y));
}

bool marishin::Point::operator==(const Point& data) const
{
  return ((x == data.x) && (y == data.y));
}

std::istream& marishin::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point point_t = { 0, 0 };
  using del = Delimeterchar;
  in >> del{ '(' } >> point_t.x >> del{ ';' } >> point_t.y >> del{ ')' };
  if (in)
  {
    point = point_t;
  }
  return in;
}

std::ostream& marishin::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool marishin::operator==(const Polygon& first, const Polygon& second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
}

double marishin::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto areaFunction = std::bind(PolygonArea{ points[1] }, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, areaFunction);
}

double marishin::PolygonArea::operator()(double area, const marishin::Point& second, const marishin::Point& third)
{
  area += 0.5 * std::abs((second.x - first.x) * (third.y - first.y) - (third.x - first.x) * (second.y - first.y));
  first = second;
  return area;
}

std::istream& marishin::operator>>(std::istream& in, marishin::Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, count, std::back_inserter(temp));
  if (in)
  {
    polygon.points = temp;
  }
  return in;
}

std::ostream& marishin::operator<<(std::ostream& out, const marishin::Polygon& polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  using output_it_t = std::ostream_iterator< Point >;
  out << polygon.points.size() << " ";
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{ out, " " });
  return out;
}

marishin::RectangleVector::RectangleVector(const Point& p1, const Point& p2):
  vertexes(marishin::Point{ p2.x - p1.x, p2.y - p1.y })
{}

double marishin::RectangleVector::operator*(const RectangleVector& p1)
{
  return (vertexes.x * p1.vertexes.x) + (vertexes.y * p1.vertexes.y);
}

double marishin::RectangleVector::getLength() const
{
  return std::sqrt(std::pow(vertexes.x, 2) + std::pow(vertexes.y, 2));
}

double marishin::RectangleVector::cos(const RectangleVector& p1)
{
  return (*this * p1) / (getLength() * p1.getLength());
}
