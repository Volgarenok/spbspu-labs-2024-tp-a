#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <vector>
#include "polygon.hpp"

namespace sivkov
{
  struct BoundingBox
  {
    Point min;
    Point max;
  };

  BoundingBox updateBoundingBox(const BoundingBox& bbox, const Point& point);
  BoundingBox addPoints(const BoundingBox& bbox, const std::vector<Point>& points, size_t index);
  BoundingBox addPoints(const BoundingBox& bbox, const std::vector<Point>& points);
  BoundingBox addPolygons(const BoundingBox& bbox, const std::vector<Polygon>& polygons, size_t index);
  BoundingBox addPolygons(const BoundingBox& bbox, const std::vector<Polygon>& polygons);
  BoundingBox calculateBoundingBox(const std::vector<Polygon>& polygons);
  bool isPointInsideBoundingBox(const Point& point, const BoundingBox& bbox);
  bool isPolygonInsideBoundingBoxRecursive(const std::vector<Point>& points, const BoundingBox& bbox, size_t index);
  bool isPolygonInsideBoundingBox(const Polygon& polygon, const BoundingBox& bbox);
}

#endif
