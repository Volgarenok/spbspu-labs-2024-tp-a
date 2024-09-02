#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <vector>
#include <functional>

namespace kuznetsov
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);

  using Pred = std::function< bool(const Polygon& polygon) >;
  double countAreaPolygon(const Polygon& polygon);
  double getAreaOddEven(std::vector< Polygon >& polygon, Pred func);
  double getAreaMean(std::vector< Polygon >& polygon);
  size_t getVertexes(const Polygon& polygon);
  void getMinOrMaxArea(std::ostream& out, std::vector< Polygon >& polygon, std::function< bool() > func);
  void getMinOrMaxVertexes(std::ostream& out, std::vector< Polygon >& polygon, std::function< bool() > func);
  size_t countPolygonWithEvenOrOddVertexes(std::vector< Polygon >& polygon, Pred func);
}

#endif
