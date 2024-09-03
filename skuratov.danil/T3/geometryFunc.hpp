#ifndef GEOMETRY_FUNC_HPP
#define GEOMETRY_FUNC_HPP

#include <iomanip>
#include "polygon.hpp"

namespace skuratov
{
  bool isEven(const Polygon& poly);
  bool isOdd(const Polygon& poly);
  double countArea(const Polygon& poly);
  double isMean(double averageArea, const Polygon& poly, size_t numOfPolygons);
  bool isNumOfVertexes(const Polygon& poly, size_t num);

  bool maxAndMinArea(const Polygon& p1, const Polygon& p2);
  bool maxAndMinVertexes(const Polygon& p1, const Polygon& p2);
  void isMaxArea(std::ostream& out, const std::vector< Polygon >& poly);
  void isMaxVertexes(std::ostream& out, const std::vector< Polygon >& poly);
  void isMinArea(std::ostream& out, const std::vector< Polygon >& poly);
  void isMinVertexes(std::ostream& out, const std::vector< Polygon >& poly);

  bool isAreaForLess(const Polygon& polygon, double area);

  bool compareByX(const Point& p1, const Point& p2);
  bool compareByY(const Point& p1, const Point& p2);
  int getMinX(const Polygon& p);
  int getMinY(const Polygon& p);
  int getMaxX(const Polygon& p);
  int getMaxY(const Polygon& p);
  Polygon createBoundingBox(const std::vector< Polygon >& poly);

  bool rightCorner(const Polygon& poly);
}

#endif
