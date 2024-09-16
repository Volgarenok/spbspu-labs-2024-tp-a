#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <map>
#include <cmath>
#include "polygon.hpp"

namespace sakovskaia
{
  double getDistance(const Point & p1, const Point & p2);
  double getAreaOfTriangle(const Point & a, const Point & b, const Point & c);
  double getAreaOfPolygon(const Polygon & polygon);
  double calculate(const std::vector< Polygon > & polygons, bool (* filter)(const Polygon &));
  bool isEven(const Polygon & p);
  bool isOdd(const Polygon & p);
  bool alwaysTrue(const Polygon &);
  bool hasVertexCount(const Polygon & p, int vertex_count);
  double countWithVertexCheck(const std::vector< Polygon > & polygons, int vertex_count);
  double getArea(const std::string & parameter, const std::vector< Polygon > & polygons);
  bool compareArea(const Polygon & lhs, const Polygon & rhs);
  bool compareVertices(const Polygon & lhs, const Polygon & rhs);
  void getMaxMin(const std::string & type, const std::vector< Polygon > & polygons);
  bool isNotEqualToPattern(const Polygon & polygon, const Polygon & pattern);
  size_t findMaxSeq(const Polygon & pattern, std::vector< Polygon >::const_iterator iter,
                    std::vector< Polygon >::const_iterator end, size_t current_max);
  void getMaxSeq(const Polygon & pattern, const std::vector< Polygon > & polygons);
  bool areEqualPolygons(const Polygon & lhs, const Polygon & rhs, const Polygon & pattern);
  void getRmecho(const Polygon & pattern, std::vector< Polygon > & polygons);
  double squaredDist(const Point & a, const Point & b);
  bool isRectangle(const Polygon & polygon);
  void getRects(const std::vector< Polygon > & polygons);
  void getCommand(const std::string & command, std::vector< Polygon > & polygons);
}
#endif
