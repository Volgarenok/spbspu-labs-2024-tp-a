#ifndef POLYGON_INFRAME_HPP
#define POLYGON_INFRAME_HPP

#include <vector>
#include <algorithm>
#include <functional>
#include "polygon.hpp"

namespace sivkov
{
  bool compareByX(const Point& a, const Point& b);
  bool compareByY(const Point& a, const Point& b);
  std::pair< Point, Point > calculateBoundingBox(const Polygon& polygon);
  Point extractMinPoint(const std::pair< Point, Point >& bbox);
  Point extractMaxPoint(const std::pair< Point, Point >& bbox);
  std::pair< Point, Point > findOverallBoundingBox(std::vector< Polygon >& polygons);
  bool pointInBounds(const Point& p, const Point& min, const Point& max);
  bool ifInFrame(const Polygon& polygon, std::pair< Point, Point > frameRectangle);
}

#endif

