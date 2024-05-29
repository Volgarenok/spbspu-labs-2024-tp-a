#ifndef GEOMETRY_FUNC_HPP
#define GEOMETRY_FUNC_HPP

#include <iomanip>
#include "polygon.hpp"

namespace skuratov
{
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  double calculateSumOfAreas(double sum, const Polygon& polygon, std::function< bool(const Polygon& polygon)> state);
  double isMean(double averageArea, const Polygon& polygon, size_t numOfPolygons);
  double isNumOfVertexes(double sumOfAreas, const Polygon& polygon, size_t numOfVertexes);

  bool maxAndMinArea(const Polygon& p1, const Polygon& p2);
  bool maxAndMinVertexes(const Polygon& p1, const Polygon& p2);
  void isMaxArea(std::ostream& out, const std::vector< Polygon >& polygon);
  void isMaxVertexes(std::ostream& out, const std::vector< Polygon >& polygon);
  void isMinArea(std::ostream& out, const std::vector< Polygon >& polygon);
  void isMinVertexes(std::ostream& out, const std::vector< Polygon >& polygon);

  bool isnumOfVertexesForCount(const Polygon& polygon, size_t num);

  bool isAreaForLess(const Polygon& polygon, double area);

  // for frameRec

  bool straightCorner(const Polygon& polygon);
}

#endif
