#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include "ReadIO.h"
#include <FormatGuard.hpp>

namespace serter
{
  struct Point
  {
    Point() : x(0), y(0)
    {}
    int x;
    int y;
    friend bool operator==(const Point& lhs, const Point& rhs)
    {
      return lhs.x == rhs.x && lhs.y == rhs.y;
    }
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

