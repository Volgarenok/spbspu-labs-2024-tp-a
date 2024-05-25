#include "polygon.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

std::istream& ibragimov::operator>>(std::istream& in, Polygon& rhs)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t n = 0;
  in >> n;
  if ((in) && (n > 2))
  {
    Polygon temp;
    std::copy_n(std::istream_iterator< Point >{in}, n, std::back_inserter(temp.points));
    if ((in) && (temp.points.size() == n))
    {
      rhs.points = std::move(temp.points);
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

size_t ibragimov::getSize(const Polygon& value)
{
  return value.points.size();
}
double ibragimov::calculateArea(const Polygon& value)
{
  std::vector< Point > points(value.points);
  points.push_back(points[0]);

  using namespace std::placeholders;
  auto multipleXY = std::bind(std::multiplies< int >{}, std::bind(getX, _1), std::bind(getY, _2));
  auto shoelace = std::bind(std::minus< int >{}, std::bind(multipleXY, _1, _2), std::bind(multipleXY, _2, _1));
  std::vector< int > dets(points.size() - 1);
  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), dets.begin(), shoelace);

  return std::abs(std::accumulate(dets.cbegin(), dets.cend(), 0.0) / 2.0);
}
ibragimov::Point ibragimov::calculateSide(const Point& lhs, const Point& rhs)
{
  return Point{lhs.x - rhs.x, lhs.y - rhs.y};
}
double ibragimov::calculateAngle(const Point& lhs, const Point& rhs)
{
  double dot = (lhs.x * rhs.x) + (lhs.y * rhs.y);
  double det = (lhs.x * rhs.y) - (lhs.y * rhs.x);
  return std::abs(std::atan2(det, dot));
}
