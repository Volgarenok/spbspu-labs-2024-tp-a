#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <numeric>
#include <functional>
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
  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);

  double calcArea(const Point& left, const Point& right);
  double getArea(const Polygon& polygon);
  double sumArea(double cur, const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool isOdd(const chernikova::Polygon& polygon);
  bool isNecessaryVertex(const chernikova::Polygon& polygon, size_t count);
  double chooseGreaterArea(double cur, const Polygon& polygon);
  size_t chooseGreaterVertexes(double cur, const Polygon& polygon);
  double chooseLessArea(double cur, const Polygon& polygon);
}

#endif
