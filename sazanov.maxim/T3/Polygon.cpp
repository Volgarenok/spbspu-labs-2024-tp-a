#include "Polygon.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "Point.hpp"

std::istream& sazanov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexes = 0;
  in >> vertexes;
  if (vertexes < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;
  temp.reserve(vertexes);
  std::copy_n(
    std::istream_iterator< Point >(in),
    vertexes,
    std::back_inserter(temp)
  );
  if (in)
  {
    polygon.points = std::move(temp);
  }
  return in;
}

double sazanov::getArea(const sazanov::Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateAreaPart = std::bind(AccumulatePolygonAreaPart{polygon.points[1]}, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0, accumulateAreaPart) / 2;
}

bool sazanov::operator==(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
}

bool sazanov::operator!=(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  return !(lhs == rhs);
}

double sazanov::AccumulatePolygonAreaPart::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}
