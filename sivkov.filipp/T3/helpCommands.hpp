#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <iomanip>
#include "polygon.hpp"

namespace sivkov
{

  struct BoundingBox
  {
    int minX;
    int maxX;
    int minY;
    int maxY;
  };

  BoundingBox calculateBoundingBox(const std::vector<Polygon>& polygons)
  {
    BoundingBox bbox{ std::numeric_limits<int>::max(), std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max(), std::numeric_limits<int>::min() };

    for (const auto& polygon : polygons)
    {
      for (const auto& point : polygon.points)
      {
        bbox.minX = std::min(bbox.minX, point.x);
        bbox.maxX = std::max(bbox.maxX, point.x);
        bbox.minY = std::min(bbox.minY, point.y);
        bbox.maxY = std::max(bbox.maxY, point.y);
      }
    }

    return bbox;
  }
  bool isPolygonInsideBoundingBox(const Polygon& polygon, const BoundingBox& bbox)
  {
    for (const auto& point : polygon.points)
    {
      if (point.x < bbox.minX || point.x > bbox.maxX || point.y < bbox.minY || point.y > bbox.maxY)
      {
        return false;
      }
    }
    return true;
  }

  struct CountAreaTriangle
  {
    Point first;
    Point second;

    double operator()(const Point& third);
  };

  double countAreaShape(const Polygon& shape)
  {
    CountAreaTriangle operation{ shape.points[0], shape.points[1] };
    std::vector< double > areas;
    std::transform(shape.points.begin() + 2, shape.points.end(), std::back_inserter(areas), operation);
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    return area;
  }

  struct CalculateArea
  {
    double operator()(const Polygon& polygon) const
    {
      return countAreaShape(polygon);
    }
  };

  struct MinArea
  {
    bool operator()(const Polygon& p1, const Polygon& p2) const
    {
      return countAreaShape(p1) < countAreaShape(p2);
    }
  };

  struct MinVertices
  {
    bool operator()(const Polygon& p1, const Polygon& p2) const
    {
      return p1.points.size() < p2.points.size();
    }
  };

  struct MaxArea
  {
    bool operator()(const Polygon& p1, const Polygon& p2) const
    {
      return countAreaShape(p1) > countAreaShape(p2);
    }
  };

  struct MaxVertices
  {
    bool operator()(const Polygon& p1, const Polygon& p2) const
    {
      return p1.points.size() > p2.points.size();
    }
  };

  double CountAreaTriangle::operator()(const Point& third)
  {
    double deltaX1 = first.x - third.x;
    double deltaY1 = second.y - third.y;
    double deltaX2 = second.x - third.x;
    double deltaY2 = first.y - third.y;

    double area = std::abs(deltaX1 * deltaY1 - deltaX2 * deltaY2) * 0.5;
    second = third;
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

  double getOddEvenMean(std::vector< Polygon >& polygon, std::string arg)
  {
    std::vector< Polygon > sortedPolygon;
    if (arg == "ODD")
    {
      std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isOddVertices);
    }
    else if (arg == "EVEN")
    {
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
