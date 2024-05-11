#ifndef UTILS_HPP
#define UTILS_HPP

#include "Geometry.hpp"

namespace petrov
{
  struct AccPolygonAreaPart
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };

  double AccPolygonAreaEO(double area, const Polygon& polygon, bool isEven);
  double AccPolygonArea(double area, const Polygon& polygon);
  double AccPolygonAreaNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes);
  bool isSmallerPolygonArea(const Polygon& p1, const Polygon& p2);
  bool isSmallerNumOfVertexes(const Polygon& p1, const Polygon& p2);
  size_t AccPolygonEON(size_t counter, const Polygon& polygon, bool isEven);
  size_t AccPolygonEON(size_t counter, const Polygon& polygon, size_t numOfVertexes);
  bool isEven(const Polygon& p);
  bool isOdd(const Polygon& p);
  bool isEqualNOV(const Polygon& p, size_t numOfVertexes);
  bool isSamePointsWithDelta(const Point& p1, const Point& p2, const Point& delta);
  bool doesExistRespectivePoint(const Point& point, const Polygon& polygon, const Point& delta);
  bool isSame(const Polygon& p1, const Polygon& p2);
  bool foo(const Point& p1, const Point& p2, const Polygon& pol1, const Polygon& pol2);
}

#endif
