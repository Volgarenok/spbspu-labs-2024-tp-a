#include "utility.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <iomanip>

namespace sivkov
{
  double CountAreaTriangle::operator()(const Point& third)
  {
    double area = std::abs((first.x - third.x) * (second.y - third.y) - (second.x - third.x) * (first.y - third.y)) * 0.5;
    second = third;
    return area;
  }

  double CalculateArea::operator()(const Polygon& polygon) const
  {
    return countAreaShape(polygon);
  }

  bool MinArea::operator()(const Polygon& p1, const Polygon& p2) const
  {
    return countAreaShape(p1) < countAreaShape(p2);
  }

  bool MinVertices::operator()(const Polygon& p1, const Polygon& p2) const
  {
    return p1.points.size() < p2.points.size();
  }

  bool MaxArea::operator()(const Polygon& p1, const Polygon& p2) const
  {
    return countAreaShape(p1) > countAreaShape(p2);
  }

  bool MaxVertices::operator()(const Polygon& p1, const Polygon& p2) const
  {
    return p1.points.size() > p2.points.size();
  }

  BoundingBox updateBoundingBox(const BoundingBox& bbox, const Point& point)
  {
    BoundingBox updatedBbox = bbox;
    if (point.x < updatedBbox.minX) updatedBbox.minX = point.x;
    if (point.x > updatedBbox.maxX) updatedBbox.maxX = point.x;
    if (point.y < updatedBbox.minY) updatedBbox.minY = point.y;
    if (point.y > updatedBbox.maxY) updatedBbox.maxY = point.y;
    return updatedBbox;
  }

  BoundingBox addPoints(const BoundingBox& bbox, const std::vector<Point>& points, size_t index = 0)
  {
    if (index == points.size()) return bbox;
    return addPoints(updateBoundingBox(bbox, points[index]), points, index + 1);
  }

  BoundingBox addPolygons(const BoundingBox& bbox, const std::vector<Polygon>& polygons, size_t index = 0)
  {
    if (index == polygons.size()) return bbox;
    return addPolygons(addPoints(bbox, polygons[index].points), polygons, index + 1);
  }

  BoundingBox calculateBoundingBox(const std::vector<Polygon>& polygons)
  {
    BoundingBox bbox{ std::numeric_limits<int>::max(), std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max(), std::numeric_limits<int>::min() };
    return addPolygons(bbox, polygons);
  }
  bool isPointInsideBoundingBox(const Point& point, const BoundingBox& bbox)
  {
    return point.x >= bbox.minX && point.x <= bbox.maxX && point.y >= bbox.minY && point.y <= bbox.maxY;
  }

  bool isPolygonInsideBoundingBoxRecursive(const std::vector<Point>& points, const BoundingBox& bbox, size_t index = 0)
  {
    if (index == points.size()) return true;
    if (!isPointInsideBoundingBox(points[index], bbox)) return false;
    return isPolygonInsideBoundingBoxRecursive(points, bbox, index + 1);
  }

  bool isPolygonInsideBoundingBox(const Polygon& polygon, const BoundingBox& bbox)
  {
    return isPolygonInsideBoundingBoxRecursive(polygon.points, bbox);
  }

  double countAreaShape(const Polygon& shape)
  {
    CountAreaTriangle operation{ shape.points[0], shape.points[1] };
    std::vector< double > areas;
    std::transform(shape.points.begin() + 2, shape.points.end(), std::back_inserter(areas), operation);
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    return area;
  }

  bool isNumEqSize(const Polygon& shape, size_t num)
  {
    return num == shape.points.size();
  }

  bool isEvenVertices(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOddVertices(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  bool hasVertexCount(const Polygon& polygon, size_t count)
  {
    return polygon.points.size() == count;
  }

  bool arePointsPermutations(const Polygon& p1, const Polygon& p2)
  {
    if (p1.points.size() != p2.points.size())
    {
      return false;
    }

    std::vector<Point> points1 = p1.points;
    std::vector<Point> points2 = p2.points;

    std::sort(points1.begin(), points1.end());
    std::sort(points2.begin(), points2.end());

    return points1 == points2;
  }

  double getOddEvenMean(std::vector<Polygon>& polygon, std::string arg)
  {
    std::vector< Polygon > sortedPolygon;
    if (arg == "ODD")
    {
      if (polygon.size() == 0)
      {
        throw std::invalid_argument("Zero size");
      }
      std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isOddVertices);
    }
    else if (arg == "EVEN")
    {
      if (polygon.size() == 0)
      {
        throw std::invalid_argument("Zero size");
      }
      std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isEvenVertices);
    }
    else
    {
      if (polygon.size() == 0)
      {
        throw std::invalid_argument("Zero size");
      }
      sortedPolygon = { polygon };
    }
    std::vector< double > areasShapes;
    std::transform(sortedPolygon.begin(), sortedPolygon.end(), std::back_inserter(areasShapes), countAreaShape);
    double area = std::accumulate(areasShapes.begin(), areasShapes.end(), 0.0);
    if (arg == "MEAN")
    {
      return area / polygon.size();
    }
    return area;
  }
}

