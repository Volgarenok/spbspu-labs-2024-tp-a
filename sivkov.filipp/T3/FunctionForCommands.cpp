#include "FunctionForcommands.hpp"
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

  double countAreaShape(const Polygon& shape)
  {
    CountAreaTriangle operation{ shape.points[0], shape.points[1], shape.points[2]};
    std::vector< double > areas;
    std::transform(shape.points.begin(), shape.points.end(), std::back_inserter(areas), operation);
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    return area;
  }

  bool compare(const Polygon& shape, size_t num)
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

    std::vector< Point > points1 = p1.points;
    std::vector< Point > points2 = p2.points;

    std::sort(points1.begin(), points1.end());
    std::sort(points2.begin(), points2.end());

    return points1 == points2;
  }

  size_t getVertexes(const Polygon& shape)
  {
    return shape.points.size();
  }

  double getOddEvenMean(std::vector<Polygon>& polygon, std::string arg)
  {
    std::vector<Polygon> sortedPolygon;

    if (arg == "ODD")
    {
      sortedPolygon.reserve(polygon.size());
      std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isOddVertices);
    }
    else if (arg == "EVEN")
    {
      sortedPolygon.reserve(polygon.size());
      std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isEvenVertices);
    }
    else if (arg == "MEAN")
    {
      if (polygon.empty())
      {
        throw std::invalid_argument("error format");
      }
      sortedPolygon = polygon;
    }
    else
    {
      throw std::invalid_argument("Invalid argument");
    }

    std::vector<double> areasShapes(sortedPolygon.size());

    std::transform(sortedPolygon.begin(), sortedPolygon.end(), areasShapes.begin(), countAreaShape);

    double area = std::accumulate(areasShapes.begin(), areasShapes.end(), 0.0);

    if (arg == "MEAN")
    {
      return area / sortedPolygon.size();
    }

    return area;
  }

  void minMaxAreas(std::ostream& out, const std::vector< Polygon >& polygon, const std::string& current)
  {
    if (polygon.size() == 0)
    {
      throw std::invalid_argument("error format");
    }
    std::vector< double > areas;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), countAreaShape);
    double minOrMax = 0.0;
    if (current == "MIN")
    {
      minOrMax = *std::min_element(areas.begin(), areas.end());
    }
    else if (current == "MAX")
    {
      minOrMax = *std::max_element(areas.begin(), areas.end());
    }
    out << std::fixed << std::setprecision(1) << minOrMax;
  }
  void minMaxVertexes(std::ostream& out, const std::vector< Polygon >& polygon, const std::string& current)
  {
    if (polygon.size() == 0)
    {
      throw std::invalid_argument("error format");
    }
    std::vector< size_t > vertexes;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexes), getVertexes);
    size_t minOrMax = 0;
    if (current == "MIN")
    {
      minOrMax = *std::min_element(vertexes.begin(), vertexes.end());
    }
    else if (current == "MAX")
    {
      minOrMax = *std::max_element(vertexes.begin(), vertexes.end());
    }
    out << minOrMax;
  }
}

