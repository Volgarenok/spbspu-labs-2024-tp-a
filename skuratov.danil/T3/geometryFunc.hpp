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

  double maxArea(const Polygon& a, const Polygon& b);
  size_t maxVertexes(const Polygon& a, const Polygon& b);
  void isMaxArea(std::ostream& out, const std::vector< Polygon >& polygons);
  void isMaxVertexes(std::ostream& out, const std::vector< Polygon >& polygons);


}

#endif
