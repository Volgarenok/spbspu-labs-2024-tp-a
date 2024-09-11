#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <delimeter.hpp>
/*
bool marishin::operator>=(const Point& first, const Point& second)
{
  return ((first.x >= second.x) && (first.y >= second.y));
}

bool marishin::operator<=(const Point& first, const Point& second)
{
  return ((first.x <= second.x) && (first.y <= second.y));
}
*/
bool marishin::operator<(const Point& first, const Point& second)
{
  return ((first.x < second.x) && (first.y < second.y));
}

bool marishin::operator==(const Point& first, const Point& second)
{
  return ((first.x == second.x) && (first.y == second.y));
}

std::istream& marishin::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp = { 0, 0 };
  using del = Delimeterchar;
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
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

struct PolygonArea
{
  marishin::Point first;
  double operator()(double area, const marishin::Point& second, const marishin::Point& third)
  {
    area += 0.5 * std::abs((third.y - first.y) * (second.x - first.x) - (third.x - first.x) * (second.y - first.y));
    first = second;
    return area;
  }
};

double marishin::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto areaFunction = std::bind(PolygonArea{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0, areaFunction);
}

std::istream& marishin::operator>>(std::istream& in, Polygon& polygon)
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

std::ostream& marishin::operator<<(std::ostream& out, const Polygon& polygon)
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
