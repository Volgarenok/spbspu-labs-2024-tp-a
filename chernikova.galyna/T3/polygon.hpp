#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <numeric>
#include <Delimiter.hpp>
#include "streamGuard.hpp"

namespace chernikova
{
  struct Point
  {
    Point() : x(0), y(0)
    {}
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, chernikova::Point& dest);
  std::istream& operator>>(std::istream& in, chernikova::Polygon& dest);

  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);

  double calcArea(const Point& left, const Point& right);
  double getArea(const Polygon& polygon);
  double sumArea(double cur, const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool isOdd(const chernikova::Polygon& polygon);
}

#endif
