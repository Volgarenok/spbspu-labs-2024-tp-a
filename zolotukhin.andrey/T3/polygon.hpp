#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <string>
#include <cstddef>
#include <numeric>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

namespace zolotukhin
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    size_t getCorners() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& poly);

  struct CalculateArea
  {
    Point point1, point2;
    double operator()(double res, const Point& point3);
  };

  struct CalcRightCorner
  {
    Point point1, point2;
    bool operator()(const Point& point3);
  };
}

#endif
