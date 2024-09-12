#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <iosfwd>
#include <vector>
#include <limits>
#include <iterator>
#include <numeric>
#include <algorithm>
#include "delimiter.hpp"

namespace sakovskaia
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream & operator>>(std::istream &, Point &);
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream &, Polygon &);
  size_t get_size(const Polygon &);
  int get_x(const Point &);
  int get_y(const Point &);
  bool operator==(const Polygon &, const Polygon &)
  bool operator==(const Point & p1, const Point & p2)
}
#endif
