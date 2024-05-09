#include "polygon.hpp"

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
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
    if ((!in) || (in.peek() != '\n'))
    {
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      in.setstate(std::ios::failbit);
    }
    else
    {
      rhs = temp;
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

size_t ibragimov::detail::getSize(const Polygon& value)
{
  return value.points.size();
}
double ibragimov::detail::getArea(const Polygon& value)
{
  std::vector< Point > points = {};
  std::copy(value.points.cbegin(), value.points.cend(), std::back_inserter(points));
  points.push_back(points[0]);

  using namespace std::placeholders;
  auto multipleXY = std::bind(std::multiplies< int >{}, std::bind(getX, _1), std::bind(getY, _2));
  auto shoelace = std::bind(std::minus< int >{}, std::bind(multipleXY, _1, _2), std::bind(multipleXY, _2, _1));
  return std::abs(std::inner_product(next(points.cbegin()), points.cend(), points.cbegin(), 0.0, std::plus< double >{}, shoelace) / 2.0);
}
ibragimov::Point ibragimov::detail::calculateSide(const ibragimov::Point& lhs, const ibragimov::Point& rhs)
{
  return Point{lhs.x - rhs.x, lhs.y - rhs.y};
}
double ibragimov::detail::calculateAngle(const ibragimov::Point& lhs, const ibragimov::Point& rhs)
{
  double dot = (lhs.x * rhs.x) + (lhs.y + lhs.y);
  double det = (lhs.x * rhs.y) - (lhs.y + lhs.x);
  return std::abs(std::atan2(det, dot));
}
