#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <iostream>

namespace petrov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Point& src);
  bool operator==(const Point& p1, const Point& p2);
  Point getDelta(const Point& p1, const Point& p2);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& in, const Polygon& src);
  bool operator==(const Polygon& p1, const Polygon& p2);

  double accPolygonAreaEO(double area, const Polygon& polygon, bool isEven);
  double accPolygonArea(double area, const Polygon& polygon);
  double accPolygonAreaNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes);
  bool isSmallerPolygonArea(const Polygon& p1, const Polygon& p2);
  bool isSmallerNumOfVertexes(const Polygon& p1, const Polygon& p2);
  size_t accPolygonEON(size_t counter, const Polygon& polygon, bool isEven);
  size_t accPolygonEON(size_t counter, const Polygon& polygon, size_t numOfVertexes);
  bool isEqualNOV(const Polygon& p, size_t numOfVertexes);
  bool isSamePointsWithDelta(const Point& p1, const Point& p2, const Point& delta);
  bool doesExistRespectivePoint(const Point& point, const Polygon& polygon, const Point& delta);
  bool isSame(const Polygon& p1, const Polygon& p2);
  bool isSameWithTwoPoints(const Point& p1, const Point& p2, const Polygon& pol1, const Polygon& pol2);
  bool isEven(const Polygon& p);
  bool isOdd(const Polygon& p);
  double getArea(const Polygon& src);
}

#endif
