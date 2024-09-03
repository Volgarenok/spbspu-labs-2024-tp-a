#include "polygon_vertices.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include "polygon.hpp"
#include "polygon_area.hpp"

namespace sivkov
{
  bool isEvenVertices(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOddVertices(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  double getOddEvenMean(std::vector< Polygon >& polygon, std::string arg)
  {
    std::vector< Polygon > sortedPolygon;

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

    std::vector< double > areasShapes(sortedPolygon.size());

    std::transform(sortedPolygon.begin(), sortedPolygon.end(), areasShapes.begin(), calculateArea);

    double area = std::accumulate(areasShapes.begin(), areasShapes.end(), 0.0);

    if (arg == "MEAN")
    {
      return area / sortedPolygon.size();
    }
    return area;
  }

  size_t countVertex(Polygon& polygon)
  {
    return polygon.points.size();
  }

  void maxVertex(std::ostream& out, const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("No polygons provided");
    }

    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertexes.begin(), countVertex);
    auto max_vertex_it = std::max_element(vertexes.begin(), vertexes.end());
    out << *max_vertex_it;
  }

  void minVertex(std::ostream& out, const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("No polygons provided");
    }

    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertexes.begin(), countVertex);
    auto min_vertex_it = std::min_element(vertexes.begin(), vertexes.end());
    out << *min_vertex_it;
  }

  bool hasVertexCount(const Polygon& polygon, size_t count)
  {
    return polygon.points.size() == count;
  }
}
