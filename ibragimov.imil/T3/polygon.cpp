#include "polygon.hpp"

#include <algorithm>
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
  int n = 0;
  in >> n;
  if (in)
  {
    rhs.points.resize(n);
    std::copy_n(std::istream_iterator< Point >{in}, n, rhs.points.begin());

    // if (n < rhs.points.size())
    // {
    //   in.setstate(std::ios::failbit);
    // }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

int ibragimov::getX(const Point& value)
{
  return value.x;
}
int ibragimov::getY(const Point& value)
{
  return value.y;
}
size_t ibragimov::getSize(const Polygon& value)
{
  return value.points.size();
}
double ibragimov::getArea(const Polygon& value)
{
  if (value.points.size() < 3)
  {
    return 0;
  }
  std::vector< Point > points = {};
  std::copy(value.points.begin(), value.points.end(), std::back_inserter(points));
  points.push_back(points[0]);

  using namespace std::placeholders;
  auto multipleCoords = std::bind(std::multiplies< int >{}, std::bind(getX, _1), std::bind(getY, _2));
  auto shoelace = std::bind(std::minus< int >{}, std::bind(multipleCoords, _1, _2), std::bind(multipleCoords, _2, _1));
  return std::abs(std::inner_product(points.begin(), points.end(), next(points.begin()), 0, std::plus<>{}, shoelace) / 2.0);
}
