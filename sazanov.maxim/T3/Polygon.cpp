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

  std::vector< Point > temp(vertexes);
  std::copy_n(
    std::istream_iterator< Point >(in),
    vertexes,
    temp.begin()
  );
  if (in)
  {
    polygon.points = std::move(temp);
  }
  return in;
}

struct GetAreaPart
{
  sazanov::Point p1;
  double operator()(const sazanov::Point& p2, const sazanov::Point& p3);
};

double sazanov::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto getAreaPart = std::bind(GetAreaPart{polygon.points[1]}, _1, polygon.points[0]);
  std::vector< double > areaParts(polygon.points.size());
  std::transform(polygon.points.cbegin(), polygon.points.cend(), areaParts.begin(), getAreaPart);
  return std::accumulate(areaParts.begin(), areaParts.end(), 0.0) / 2;
}

bool sazanov::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
}

bool sazanov::operator!=(const Polygon& lhs, const Polygon& rhs)
{
  return !(lhs == rhs);
}

double GetAreaPart::operator()(const sazanov::Point& p2, const sazanov::Point& p3)
{
  double area = std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}
