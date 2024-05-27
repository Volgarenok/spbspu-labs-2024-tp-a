#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace yakshieva
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  bool operator==(const Point& p1, const Point& p2);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& p1, const Polygon& p2);
  bool isVertexEven(const Polygon& polygon);
  bool isVertexOdd(const Polygon& polygon);
  bool hasNumOfVertices(const Polygon& polygon, size_t numOfVertices);
}

#endif
