#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <numeric>
#include <functional>
#include <delimiter.hpp>
#include <streamGuard.hpp>
#include "point.hpp"

namespace chernikova
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);

  using Predicat = bool (*) (const Polygon&);

  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  double calcArea(const Point& lhs, const Point& rhs);
  double calcAreaForPoint(const Point& point);
  double getArea(const Polygon& polygon);
  size_t getVertexes(const Polygon& polygon);
  bool isNecessaryVertex(const Polygon& polygon, size_t count);
  std::vector< double > getVectorArea(const std::vector< Polygon >& polygons);
  std::vector< size_t > getVectorVertexes(const std::vector< Polygon >& polygons);

  void getAreaByPredicat(const std::vector< Polygon >& polygons, std::ostream& out, Predicat predicat);
  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountByPredicat(const std::vector< Polygon >& polygons, std::ostream& out, Predicat predicat);
  void getCountEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs);
  bool hasIntersection(const Polygon& lhs, const Polygon& rhs);
  bool isRightAngleByThreePoints(const Point* p1, const Point* p2, const Point* p3);
  bool isRightAngle(const Point& p);
  bool hasRightAngle(const Polygon& polygon);

  void echo(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
  void intersections(const std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
  void rightShapes(const std::vector< Polygon >& polygons, std::ostream& out);
}

#endif
