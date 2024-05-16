#include "Polygon.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <iomanip>
#include "Point.hpp"
#include "StreamGuard.hpp"

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

double sazanov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateAreaPart = std::bind(AccumulatePolygonAreaPart{points[1]}, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, accumulateAreaPart) / 2;
}

bool sazanov::Polygon::operator==(const sazanov::Polygon& rhs) const
{
  if (points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(this->points.begin(), this->points.end(), rhs.points.begin());
}

double sazanov::AccumulatePolygonAreaPart::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}
