#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>
#include <numeric>

namespace kozakova
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& value);
  bool operator<(const Point& p1, const Point& p2);
  bool operator==(const Point& p1, const Point& p2);


  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& value);
  double getArea(const Polygon& p);
  bool isRect(const Polygon& p);
  bool operator==(const Polygon& p1, const Polygon& p2);
  bool isPerpendicular(const Point& p1, const Point& p2, const Point& p3);
  bool isOddCountVertexes(const Polygon& p);
  bool isEvenCountVertexes(const Polygon& p);
  bool isNCountVertexes(const Polygon& p, size_t n);
  bool minArea(const Polygon& p1, const Polygon& p2);
  bool minVertexes(const Polygon& p1, const Polygon& p2);
}
#endif
