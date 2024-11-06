#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <functional>
#include <iostream>
#include <numeric>
#include <algorithm>

#include "../common/delimiter.hpp"

namespace kovtun
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct right_cross
  {
    double operator()(const Point & a, const Point & b) const;
  };

  struct left_cross
  {
    double operator()(const Point & a, const Point & b) const;
  };

  std::istream & operator>>(std::istream & in, Polygon & polygon);
  bool operator==(const Polygon &, const Polygon &);
  bool operator==(const Point &, const Point &);

  double getArea(const Polygon & polygon);
}

#endif
