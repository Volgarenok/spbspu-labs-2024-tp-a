#include "polygon_inframe.hpp"
#include <vector>
#include <algorithm>
#include <functional>
#include "polygon.hpp"

namespace sivkov
{
  bool compareByX(const Point& a, const Point& b)
  {
    return a.x < b.x;
  }

  bool compareByY(const Point& a, const Point& b)
  {
    return a.y < b.y;
  }

  std::pair< Point, Point > calculateBoundingBox(const Polygon& polygon)
  {
    auto minMaxX = std::minmax_element(polygon.points.begin(), polygon.points.end(), compareByX);
    auto minMaxY = std::minmax_element(polygon.points.begin(), polygon.points.end(), compareByY);
    return { {minMaxX.first->x, minMaxY.first->y}, {minMaxX.second->x, minMaxY.second->y} };
  }

  Point extractMinPoint(const std::pair< Point, Point >& bbox)
  {
    return bbox.first;
  }

  Point extractMaxPoint(const std::pair< Point, Point >& bbox)
  {
    return bbox.second;
  }

  std::pair< Point, Point > findOverallBoundingBox(std::vector< Polygon >& polygons)
  {
    std::vector< std::pair< Point, Point > > boundingBoxes(polygons.size());
    Polygon combinedBounds;

    std::transform(polygons.begin(), polygons.end(), boundingBoxes.begin(), calculateBoundingBox);

    combinedBounds.points.reserve(2 * polygons.size());
    std::transform(boundingBoxes.begin(), boundingBoxes.end(), std::back_inserter(combinedBounds.points), extractMinPoint);
    std::transform(boundingBoxes.begin(), boundingBoxes.end(), std::back_inserter(combinedBounds.points), extractMaxPoint);

    return calculateBoundingBox(combinedBounds);
  }

  bool pointInBounds(const Point& p, const Point& min, const Point& max)
  {
    return (p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y);
  }

  bool ifInFrame(const Polygon& polygon, std::pair< Point, Point > frameRectangle)
  {
    auto operation = std::bind(pointInBounds, std::placeholders::_1, frameRectangle.first, frameRectangle.second);
    size_t count = std::count_if(polygon.points.begin(), polygon.points.end(), operation);
    return count == polygon.points.size();
  }
}

