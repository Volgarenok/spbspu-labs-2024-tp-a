#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include "Polygon.hpp"

namespace stepanchenko
{
  double areaEven(const std::vector< Polygon >& polygons);
  double areaOdd(const std::vector< Polygon >& polygons);
  double areaMean(const std::vector< Polygon >& polygons);
  double areaNum(const std::vector< Polygon >& polygons, size_t nVertexes);
  double getArea(const Polygobool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  int multiply_points(const Point& a, const Point& b);
  bool hasNumOfVertexes(const stepanchenko::Polygon& polygon, const size_t& num);
}

#endif
