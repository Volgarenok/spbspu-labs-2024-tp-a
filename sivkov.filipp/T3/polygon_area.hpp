#ifndef POLYGON_AREA_HPP
#define POLYGON_AREA_HPP

#include "polygon.hpp"

namespace sivkov
{
  double calculateArea(const Polygon& polygon);
  void maxArea(std::ostream& out, const std::vector< Polygon >& polygons);
  void minArea(std::ostream& out, const std::vector< Polygon >& polygons);
}
#endif
