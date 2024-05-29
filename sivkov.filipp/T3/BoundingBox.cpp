#include "BoundingBox.hpp"

namespace sivkov
{

  BoundingBox updateBoundingBox(const BoundingBox& bbox, const Point& point)
  {
    BoundingBox updatedBbox = bbox;
    updatedBbox.min.x = std::min(updatedBbox.min.x, point.x);
    updatedBbox.max.x = std::max(updatedBbox.max.x, point.x);
    updatedBbox.min.y = std::min(updatedBbox.min.y, point.y);
    updatedBbox.max.y = std::max(updatedBbox.max.y, point.y);
    return updatedBbox;
  }

  BoundingBox addPoints(const BoundingBox& bbox, const std::vector<Point>& points, size_t index)
  {
    if (index == points.size())
    {
      return bbox;
    }
    return addPoints(updateBoundingBox(bbox, points[index]), points, index + 1);
  }

  BoundingBox addPoints(const BoundingBox& bbox, const std::vector<Point>& points)
  {
    return addPoints(bbox, points, 0);
  }

  BoundingBox addPolygons(const BoundingBox& bbox, const std::vector<Polygon>& polygons, size_t index)
  {
    if (index == polygons.size())
    {
      return bbox;
    }
    return addPolygons(addPoints(bbox, polygons[index].points), polygons, index + 1);
  }

  BoundingBox addPolygons(const BoundingBox& bbox, const std::vector<Polygon>& polygons)
  {
    return addPolygons(bbox, polygons, 0);
  }

  BoundingBox calculateBoundingBox(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Polygon list is empty");
    }
    const Polygon& firstPolygon = polygons[0];
    if (firstPolygon.points.empty())
    {
      throw std::invalid_argument("First polygon has no points");
    }

    BoundingBox bbox = { firstPolygon.points[0], firstPolygon.points[0] };
    bbox = addPoints(bbox, firstPolygon.points, 1);
    return addPolygons(bbox, polygons, 1);
  }

  bool isPointInsideBoundingBox(const Point& point, const BoundingBox& bbox)
  {
    return point.x >= bbox.min.x && point.x <= bbox.max.x && point.y >= bbox.min.y && point.y <= bbox.max.y;
  }

  bool isPolygonInsideBoundingBoxRecursive(const std::vector<Point>& points, const BoundingBox& bbox, size_t index)
  {
    if (index == points.size())
    {
      return true;
    }
    if (!isPointInsideBoundingBox(points[index], bbox))
    {
      return false;
    }
    return isPolygonInsideBoundingBoxRecursive(points, bbox, index + 1);
  }

  bool isPolygonInsideBoundingBox(const Polygon& polygon, const BoundingBox& bbox)
  {
    return isPolygonInsideBoundingBoxRecursive(polygon.points, bbox, 0);
  }
}
